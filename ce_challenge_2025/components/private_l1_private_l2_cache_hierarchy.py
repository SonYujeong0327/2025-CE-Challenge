# Copyright (c) 2024 Arm Limited
# All rights reserved.
#
# The license below extends only to copyright in the software and shall
# not be construed as granting a license to any other intellectual
# property including but not limited to intellectual property relating
# to a hardware implementation of the functionality of the software
# licensed hereunder.  You may use the software subject to the license
# terms below provided that you ensure that this notice is replicated
# unmodified and in its entirety in all distributions of the software,
# modified or unmodified, in source code or in binary form.
#
# Copyright (c) 2021 The Regents of the University of California
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met: redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer;
# redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution;
# neither the name of the copyright holders nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

from typing import Optional

from m5.objects import (
    BadAddr,
    BaseCPU,
    BaseXBar,
    Cache,
    L2XBar,
    Port,
    SystemXBar,
)

from gem5.isas import ISA
from gem5.utils.override import *
from gem5.components.boards.abstract_board import AbstractBoard
from gem5.components.cachehierarchies.abstract_cache_hierarchy import AbstractCacheHierarchy
from gem5.components.cachehierarchies.abstract_two_level_cache_hierarchy import AbstractTwoLevelCacheHierarchy
from gem5.components.cachehierarchies.classic.abstract_classic_cache_hierarchy import AbstractClassicCacheHierarchy

from components.caches.l1dcache import L1DCacheCustom
from components.caches.l1icache import L1ICacheCustom
from components.caches.l2cache import L2CacheCustom

class PrivateL1PrivateL2CacheHierarchyCustom(
    AbstractClassicCacheHierarchy, AbstractTwoLevelCacheHierarchy
):   
    def _get_default_membus(self) -> SystemXBar:
        """
        A method used to obtain the default memory bus of 64 bit in width for
        the PrivateL1PrivateL2 CacheHierarchy.

        :returns: The default memory bus for the PrivateL1PrivateL2
                  CacheHierarchy.

        """
        membus = SystemXBar(width=64)
        membus.badaddr_responder = BadAddr()
        membus.default = membus.badaddr_responder.pio
        return membus

    def __init__(
        self,
        l1d_size: str,
        l1d_assoc: int,
        l1i_size: str,
        l1i_assoc: int,
        l2_size: str,
        l2_assoc: int,
        l1i_tag_latency: int = 1,
        l1i_data_latency: int = 1,
        l1i_prefetch_type: str = "tagged",
        l1i_prefetch_degree: int = 2,
        l1d_tag_latency: int = 1,
        l1d_data_latency: int = 1,
        l1d_prefetch_type: str = "stride",
        l1d_prefetch_degree: int = 4,
        l2_tag_latency: int = 1,
        l2_data_latency: int = 2,
        l2_prefetch_type:  str = "stride",
        l2_prefetch_degree:  int = 8,
        membus: Optional[BaseXBar] = None,
    ) -> None:
        """
        :param l1d_size: The size of the L1 Data Cache (e.g., "32kB").

        :param  l1i_size: The size of the L1 Instruction Cache (e.g., "32kB").

        :param l2_size: The size of the L2 Cache (e.g., "256kB").

        :param membus: The memory bus. This parameter is optional parameter and
                       will default to a 64 bit width SystemXBar is not
                       specified.
        """

        AbstractClassicCacheHierarchy.__init__(self=self)
        AbstractTwoLevelCacheHierarchy.__init__(
            self,
            l1i_size=l1i_size,
            l1i_assoc=l1i_assoc,
            l1d_size=l1d_size,
            l1d_assoc=l1d_assoc,
            l2_size=l2_size,
            l2_assoc=l2_assoc,
       )
        # Need leading underscores because SimObject (SubSystem) does not have these attributes as
        # parameters
        self._l1i_prefetch_type   = l1i_prefetch_type     
        self._l1i_prefetch_degree = l1i_prefetch_degree     
        self._l1d_prefetch_type   = l1d_prefetch_type     
        self._l1d_prefetch_degree = l1d_prefetch_degree     
        self._l2_prefetch_type    = l2_prefetch_type     
        self._l2_prefetch_degree  = l2_prefetch_degree     
        self.membus = membus if membus else self._get_default_membus()


    @overrides(AbstractClassicCacheHierarchy)
    def get_mem_side_port(self) -> Port:
        return self.membus.mem_side_ports

    @overrides(AbstractClassicCacheHierarchy)
    def get_cpu_side_port(self) -> Port:
        return self.membus.cpu_side_ports

    @overrides(AbstractCacheHierarchy)
    def incorporate_cache(self, board: AbstractBoard) -> None:
        # Set up the system port for functional access from the simulator.
        board.connect_system_port(self.membus.cpu_side_ports)

        for _, port in board.get_memory().get_mem_ports():
            self.membus.mem_side_ports = port

        self.l2buses = [
            L2XBar() for i in range(board.get_processor().get_num_cores())
        ]

        for i, cpu in enumerate(board.get_processor().get_cores()):
            l2_node = self.add_root_child(
                f"l2-cache-{i}", L2CacheCustom( size=self._l2_size, assoc=self._l2_assoc,
                                                prefetch_type=self._l2_prefetch_type,
                                                prefetch_degree=self._l2_prefetch_degree)
            )
            l1i_node = l2_node.add_child(
                f"l1i-cache-{i}", L1ICacheCustom(size=self._l1i_size, assoc=self._l1i_assoc,
                                                 prefetch_type=self._l1i_prefetch_type,
                                                 prefetch_degree=self._l1i_prefetch_degree)
            )
            l1d_node = l2_node.add_child(
                f"l1d-cache-{i}", L1DCacheCustom(size=self._l1d_size, assoc=self._l1d_assoc,
                                                 prefetch_type=self._l1d_prefetch_type,
                                                 prefetch_degree=self._l1d_prefetch_degree)
            )

            self.l2buses[i].mem_side_ports = l2_node.cache.cpu_side
            self.membus.cpu_side_ports = l2_node.cache.mem_side

            l1i_node.cache.mem_side = self.l2buses[i].cpu_side_ports
            l1d_node.cache.mem_side = self.l2buses[i].cpu_side_ports

            cpu.connect_icache(l1i_node.cache.cpu_side)
            cpu.connect_dcache(l1d_node.cache.cpu_side)

            self._connect_table_walker(i, cpu)

            if board.get_processor().get_isa() == ISA.X86:
                int_req_port = self.membus.mem_side_ports
                int_resp_port = self.membus.cpu_side_ports
                cpu.connect_interrupt(int_req_port, int_resp_port)
            else:
                cpu.connect_interrupt()

        if board.has_coherent_io():
            self._setup_io_cache(board)

    def _connect_table_walker(self, cpu_id: int, cpu: BaseCPU) -> None:
        cpu.connect_walker_ports(
            self.membus.cpu_side_ports, self.membus.cpu_side_ports
        )

    def _setup_io_cache(self, board: AbstractBoard) -> None:
        """Create a cache for coherent I/O connections"""
        self.iocache = Cache(
            assoc=8,
            tag_latency=50,
            data_latency=50,
            response_latency=50,
            mshrs=20,
            size="4kB",
            tgts_per_mshr=12,
            addr_ranges=board.mem_ranges,
        )
        self.iocache.mem_side = self.membus.cpu_side_ports
        self.iocache.cpu_side = board.get_mem_side_coherent_io_port()
