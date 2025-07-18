#!/bin/bash

TESTLIST=$1
OUTDIR=$2
PRED=$3
NUM_THREADS=$4

bench_list=()
type_list=()
graph_list=()
it_list=()

while read line; do
    bench_list+=($(echo "$line" | cut -d' ' -f1))
    it_list+=($(echo "$line" | cut -d' ' -f2))
done < "$TESTLIST"

start_i=0
end_i=$NUM_THREADS
list_len=${#bench_list[@]}
done_cnt=0

test_list=()

while [ $done_cnt -lt $list_len ];
do    
    if [[ ${list_len} -lt ${end_i} ]]; then
        end_i=$list_len
    fi
    
    pids=()
    sids=()
    for (( k=$start_i;  k<${end_i}; k++ ));
    do
        BENCH=${bench_list[$k]}
        NUM_IT=${it_list[$k]}

        test_list+=("${BENCH}_${NUM_IT}")
        # Run the gem5 commands in parallel
        ${GEM5_PATH}/build/RISCV/gem5.opt -re --outdir=${OUTDIR}/TSVC/${BENCH}_${NUM_IT} ${CE_RUN_PATH}/scripts/run-ce-challenge-TSVC.py -b $BENCH -n $NUM_IT --pred $PRED &
    
        pids+=($!)
        sids+=($k)
    done

    
    # Loop to wait for each process and echo a message when it finishes
    for i in "${!pids[@]}"; do
        wait ${pids[$i]} && echo "TSVC ${test_list[$i+$start_i]} with sid ${sids[$i]} finished"
        ((done_cnt++))
    done
    
    # Wait for all background jobs to finish
    wait
    start_i=$end_i
    end_i=$(($start_i + ${NUM_THREADS}))
done

echo "=== Parsing Stat Data to ${OUTDIR}/tsvc_result.stat ==="

HEADER_STR="target num_inst cpi sim_sec num_ops condPredicted condIncorrect commitTotal commitMissTotal HostRuntime(s) AverageTime" 
echo ${HEADER_STR} > ${OUTDIR}/tsvc_result.stat

for run in "${test_list[@]}"; do
    python3 ${CE_RUN_PATH}/scripts/tsvc_parse_out.py ${OUTDIR}/TSVC/${run} ${OUTDIR}/tsvc_result.stat
done
cat ${OUTDIR}/tsvc_result.stat
