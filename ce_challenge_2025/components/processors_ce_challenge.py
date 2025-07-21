# Copyright (c) 2022 The Regents of the University of California
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

from gem5.isas import ISA
from gem5.components.processors.base_cpu_core import BaseCPUCore
from gem5.components.processors.base_cpu_processor import BaseCPUProcessor

from m5.objects import RiscvO3CPU 
from m5.objects.FuncUnitConfig import *
from m5.objects.BranchPredictor import * 
###See: /root/gem5/src/cpu/pred/BranchPredictor.py for available branch predictors and their parameters

####################################################################
###### TODO TODO CONNECT YOUR BRANCH PREDICTOR HERE TODO TODO ######
##### FEEL FREE TO REPLACE THE BASE BP (TournamentBP->LocalBP) #####
##### OR CREATE YOUR OWN CUSTOM BP MODEL.                      #####
##### IT SHOULD STILL BE DECLARED AS MyCeChallengeBP BELOW AND #####
##### CONNECT TO THE CeChallenge Core ##############################
####################################################################
class MyCeChallengeBP(TournamentBP):
    localPredictorSize = 4096

####################################################################
####################################################################

###################################################################################################################################
############################ NO NEED TO MODIFY ANYTHING PAST HERE    ##############################################################
###################################################################################################################################

#################################################
#### DO NOT MODIFY CPU CONFIGURATION ############
#### OUTSIDE OF THE BRANCH PREDICTOR ############
#################################################
class O3CPUCeChallenge(RiscvO3CPU): 
    def __init__(self, fetch_width, width, rob_size, num_int_regs, num_fp_regs, num_lq_entries, num_sq_entries,
                       bp_type):
        """
        :param width: sets the width of fetch, decode, raname, issue, wb, and
        commit stages.
        :param rob_size: determine the number of entries in the reorder buffer.
        :param num_int_regs: determines the size of the integer register file.
        :param num_int_regs: determines the size of the vector/floating point
        register file.
        """
        super().__init__()
        self.fetchWidth = fetch_width
        self.decodeWidth = width
        self.renameWidth = width
        self.issueWidth = width
        self.wbWidth = width
        self.commitWidth = width

        self.numROBEntries = rob_size

        self.numPhysIntRegs = num_int_regs
        self.numPhysFloatRegs = num_fp_regs

        if (bp_type == "tournament" or bp_type == "tourney" or bp_type == "ref"):
            self.branchPred = TournamentBP()
        elif (bp_type == "local"):
            self.branchPred = LocalBP()
        elif (bp_type == "MyBP"):
            self.branchPred = MyCeChallengeBP()
        else:
            self.branchPred = TournamentBP()

        self.LQEntries = num_lq_entries
        self.SQEntries = num_sq_entries

class O3CPUStdCeChallenge(BaseCPUCore):
    def __init__(self, fetch_width, width, rob_size, num_int_regs, num_fp_regs, num_lq_entries, num_sq_entries, bp_type):
        """
        :param width: sets the width of fetch, decode, raname, issue, wb, and
        commit stages.
        :param rob_size: determine the number of entries in the reorder buffer.
        :param num_int_regs: determines the size of the integer register file.
        :param num_int_regs: determines the size of the vector/floating point
        register file.
        """
        core = O3CPUCeChallenge(fetch_width, width, rob_size, num_int_regs, num_fp_regs, num_lq_entries, num_sq_entries, bp_type)
        super().__init__(core, ISA.RISCV) 


class O3CPUCeChallengeBase(BaseCPUProcessor):
    def __init__(self, fetch_width, width, rob_size, num_int_regs, num_fp_regs, num_lq_entries, num_sq_entries, bp_type):
        """
        :param width: sets the width of fetch, decode, raname, issue, wb, and
        commit stages.
        :param rob_size: determine the number of entries in the reorder buffer.
        :param num_int_regs: determines the size of the integer register file.
        :param num_int_regs: determines the size of the vector/floating point
        register file.
        """
        cores = [O3CPUStdCeChallenge(fetch_width, width, rob_size, num_int_regs, num_fp_regs, num_lq_entries, num_sq_entries, bp_type)]
        super().__init__(cores)
        self._width = width
        self._fetch_width = fetch_width
        self._rob_size = rob_size
        self._num_int_regs = num_int_regs
        self._num_fp_regs = num_fp_regs
        self._num_lq_entries = num_lq_entries
        self._num_sq_entries = num_sq_entries
        self._bp_type = bp_type

    def get_area_score(self):
        """
        :returns the area score of a pipeline using its parameters width,
        rob_size, num_int_regs, and num_fp_regs.
        """
        score = (
            self._width
            * (2 * self._rob_size + self._num_int_regs + self._num_fp_regs)
            + 3 * self._width
            + self._fetch_width
            + 2 * self._rob_size
            + self._num_int_regs
            + self._num_fp_regs
        )
        return score

class CeChallengeCPU(O3CPUCeChallengeBase):
    def __init__(
        self,
        bp_type: str = "tournament",
        fetch_width: int = 8,
        width: int = 4,
        rob_size: int = 128,
        num_int_regs: int = 128,
        num_fp_regs: int = 128,
        num_lq_entries: int = 32,
        num_sq_entries: int = 32,
    ):
        super().__init__(
            fetch_width=fetch_width,
            width=width,
            rob_size=rob_size,
            num_int_regs=num_int_regs,
            num_fp_regs=num_fp_regs,
            num_lq_entries=num_lq_entries,
            num_sq_entries=num_sq_entries,
            bp_type=bp_type
        )



































































































































































































































