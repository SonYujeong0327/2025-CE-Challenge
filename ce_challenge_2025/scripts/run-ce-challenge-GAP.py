from argparse import ArgumentParser
from gem5.components.boards.simple_board import SimpleBoard
from gem5.components.processors.simple_processor import SimpleProcessor
from gem5.components.memory.memory import ChanneledMemory
from gem5.resources.resource import obtain_resource
from gem5.resources.resource import BinaryResource
from gem5.simulate.simulator import Simulator
from m5.objects import DDR4_2400_8x8
from pathlib import Path
# For SimpleProcessor
from gem5.components.processors.cpu_types import CPUTypes
from gem5.isas import ISA


############### Custom Scripts ############################
import sys
import os
components_path = os.environ.get('CE_RUN_PATH')
sys.path.append(components_path)
from components.processors_ce_challenge import *
from components.private_l1_private_l2_cache_hierarchy import PrivateL1PrivateL2CacheHierarchyCustom
print(f"gem5 component path specified: {components_path}");
#########################################################

gaps_binary_path = os.environ.get('GAP_BINARY_PATH')
print(f"GAP BINARY PATH specified: {gaps_binary_path}");


# A simple script to run ce challenge HW platform with GAP benchmarks
# In general run with the following command
    # gem5 [optional: --outdir=<processor-type>-proc] run-ce-challenge-single.py -b <bench> -t <graph_type> -g <graph_size> -n <iteration> 
    # graph type should be g (Kronecker graph ) or u (uniform random)

# *** Argument Parsing ***

USAGE = """ A run script to run GAP benchmark on ce challenge HW platform.

Example usage:

gem5 --outdir=<dir> run-ce-challenge-GAP.py -b bfs -t g -g 4 -n 10
"""

parser = ArgumentParser(description=USAGE)
parser.add_argument(
    "-p",
    "--pred",
    nargs='?',
    const=1, default="MyBP",
    type=str,
    help="Type of branch predictor: ref (tournament), local, MyBP (predictor submitted for ce challenge",
    required=False,
)

parser.add_argument(
    "-b",
    "--bench",
    nargs='?',
    const=1, default="bfs",
    type=str,
    help="Name of GAP benchmark to run (bfs, cc, cc_sv, sssp, tc, pr, pr_spmv, bc)",
    required=True,
)

parser.add_argument(
    "-t",
    "--type",
    nargs='?',
    const=1, default="g",
    type=str,
    help="type of graph. g - Kronecker graph.  u - uniform random",
    required=False,
)

parser.add_argument(
    "-g",
    "--graph",
    nargs='?',
    const=1, default=10,
    type=int,
    help="Name of verticies in a graph (power of 2)",
    required=False,
)

parser.add_argument(
    "-f",
    "--file",
    nargs='?',
    const=1, default="roadU.sg",
    type=str,
    help="Name of graphs in gapbs dir. For loading graph instead of generating",
    required=False,
)

parser.add_argument(
    "-n",
    "--num_it",
    nargs='?',
    const=1, default=10,
    type=int,
    help="Name of iterations.",
    required=False,
)

arguments = parser.parse_args()

if (arguments.type == "g"):
    graph_type = "-g"
elif (arguments.type == "u"):
    graph_type = "-u"
else:
    graph_type = "-g"
    print(f"Error: {arguments.type} is not a valid graph type. Should be g or u. Defaulting to g")
    
##############################################################################################
# *** Setting up the board and running the workload ***
##### DO NOT CHANGE ##### DO NOT CHANGE ##### DO NOT CHANGE ######## DO NOT CHANGE ###########
##### DO NOT CHANGE ##### DO NOT CHANGE ##### DO NOT CHANGE ######## DO NOT CHANGE ###########
############################## Cache Options #################################################
l1_size="32KiB"
l1_assoc=8
l2_size="512KiB"
l2_assoc=8
cache_hierarchy = PrivateL1PrivateL2CacheHierarchyCustom(
    l1i_size=l1_size, l1i_assoc=l1_assoc,  l1i_data_latency=1,
    l1i_prefetch_type = "tagged",   l1i_prefetch_degree=2,      #L1I prefetcher parameters
    l1d_size=l1_size, l1d_assoc=l1_assoc,  l1d_data_latency=1,
    l1d_prefetch_type = "tagged",   l1d_prefetch_degree=2,      #L1D prefetcher parameters
    l2_size=l2_size,  l2_assoc=l2_assoc,  l2_data_latency=2,
    l2_prefetch_type  = "tagged",   l2_prefetch_degree=4,       #L2 prefetcher parameters
)
###############################################################################################

################### Core Option #########################################
print("==== Running {arguments.pred} branch predictor ====")
processor = CeChallengeCPU(arguments.pred)

memory = ChanneledMemory(
    dram_interface_class=DDR4_2400_8x8,
    num_channels=2,
    interleaving_size=128,
    size="8 GiB",
)

board = SimpleBoard(
    clk_freq="1GHz",
    processor=processor,
    memory=memory,
    cache_hierarchy=cache_hierarchy
)

binary_path = Path(f"{gaps_binary_path}/{arguments.bench}")
board.set_se_binary_workload(
    binary = BinaryResource(
        local_path=binary_path.as_posix()
    ),
arguments=[graph_type, str(arguments.graph), "-n", str(arguments.num_it)],
)

simulator = Simulator(board=board)
simulator.run()

print(f"==== RUN COMPLETE ===")
print(f"Ran a total of {simulator.get_current_tick() / 1e12} simulated seconds")
##### DO NOT CHANGE ##### DO NOT CHANGE ##### DO NOT CHANGE ######## DO NOT CHANGE ###########
##### DO NOT CHANGE ##### DO NOT CHANGE ##### DO NOT CHANGE ######## DO NOT CHANGE ###########
