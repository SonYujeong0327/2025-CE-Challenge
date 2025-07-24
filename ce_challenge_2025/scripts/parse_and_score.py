import sys
import os

stat_path    = sys.argv[1]
reftime_path = sys.argv[2]
accum_score  = sys.argv[3]


candidate_times = []
ref_times = []

header_passed=False

with open(stat_path, "r") as statfile:
    for line in statfile:
        if header_passed:
            line = line.split()
            candidate_times.append(float(line[-1]))
        else:
            header_passed=True

header_passed=False
with open(reftime_path, "r") as reffile:
    for line in reffile:
        if header_passed:
            ref_times.append(float(line))
        else:
            header_passed=True

if len(candidate_times) != len(ref_times):
    print("ERROR: Result and Reference Time mismatch. Check the reftime file has same number of entries as the result file")
    sys.exit(1)

speedup_list = []
geomean = 1.0
for candidate, ref in zip(candidate_times, ref_times):
    if (ref == 0.0 or candidate == 0.0):
        print("ERROR: Can't get geomean when ther is a zero value")
        sys.exit(1)
    speedup = ref/candidate
    geomean = geomean * speedup
    speedup_list.append(speedup)

geomean = geomean**(1.0/len(speedup_list))

final_score = geomean + float(accum_score)
print(f"SCORE: {final_score:.5f}")


