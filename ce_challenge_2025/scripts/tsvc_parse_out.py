import sys

targetname = sys.argv[1]
outname    = sys.argv[2]

with open(outname, "a") as outfile:
#    header = "target, bench, num_inst, cpi, sim_sec, num_ops, condPredicted, condIncorrect,  commitTotal, commitMissTotal, AverageTime, host_seconds\n"
#    outfile.write(header)

        stats_file = f"{targetname}/stats.txt"
        # Open the file

        # default values in case no cache miss
        sim_sec = "0"
        host_seconds = "0"
        num_inst = "0" 
        num_ops = "0" 
        cpi = "0" 
        condPredicted = "0"
        condIncorrect = "0"
        condPredictedTaken = "0"        
        NotTakenMispredicted = "0"
        TakenMispredicted = "0"
        commitTotal = "0"
        commitMissTotal = "0"

        with open(stats_file, "r") as file:
            # Read the file line by line
            for line in file:
                words = line.split()

                # Split the line into values
                if "simSeconds" in line:
                    sim_sec = words[1]
                elif "hostSeconds" in line:
                    host_seconds = words[1]
                elif "board.processor.cores.core.commitStats0.numInsts" in line:
                    num_inst = words[1]
                elif "board.processor.cores.core.commitStats0.numOps"  in line:
                    num_ops = words[1]
                elif "board.processor.cores.core.commitStats0.cpi"    in line:
                    cpi = words[1]
                elif "board.processor.cores.core.branchPred.condPredicted " in line:
                    condPredicted = words[1]
                elif "board.processor.cores.core.branchPred.condIncorrect" in line:               
                    condIncorrect = words[1]
                elif "board.processor.cores.core.branchPred.committed_0::total" in line:
                    commitTotal = words[1]
                elif "board.processor.cores.core.branchPred.mispredicted_0::total" in line:
                    commitMissTotal = words[1]


        bench_stdout_file = f"{targetname}/simout.txt"
        avg_time = 0.0
        with open(bench_stdout_file, "r") as file:
            for line in file:
                if "Ran a total of" in line:
                    line = line.split()
                    avg_time = line[4]

        minimal = [ targetname, num_inst, cpi, sim_sec, num_ops,  
                    condPredicted, condIncorrect, 
                    commitTotal, commitMissTotal,
                    host_seconds, str(avg_time)
                  ]
    
        outfile.write(" ".join(minimal) + "\n")
    
