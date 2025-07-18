# CE Challenge Run Environment

This is the repository for running the CE Challenge 2025 environment. 
It contains the run script for the gem5 with CE challenge HW configuration, 
along with self test evaluation to run the GAP and TSVC benchmarks to generate the performance score.

## Getting Started

Make sure to set the correct binary and directory paths in env.sh
Each of the GAP and TSVC binaries you generated should be contained in single directory.

Once the correct binary paths and gem5 install paths are setup, run: 

```bash
source env.sh 
```


## Executing Self Test

You can run the self test by performing:

```bash
./RUN_SELF_TEST
```

This will go run the "MyBP" predictor and run all the benchmarks that are going to be used for evaluation.
At the end of the execution, it will generate the final score for the given predictor.

Once you make modification to your compiler and change your binaries, make sure to update the binary paths `GAP_BINARY_PATH` and `TSVC_BINARY_PATH` in the `env.sh`

## Modifying "MyBP" predictor configuration

You can modify the MyBP predictor in: `components/processors_ce_challenge.py`
`MyCeChallengeBP()` class is the `BranchPredictor` module that you will be submitting for evaluation.

By default, it is using the `TournamentBP()`, but with a slightly bigger local predictor size compared to the reference model.
You my change the existing predictor parameters, use a different branch predictor already provided by the gem5 platform,
or create your own custom branch predictor in C++ at `gem5/src/cpu/pred/`. 

If you are building your own branch predictor in C, don't forget to add it to the `gem5/src/cpu/pred/SConscript` and re-build the gem5 simulator.
Make sure to submit all the files you changed or added in `gem5/src/cpu/pred/`.


## Building gem5

To build gem5, go to the gem5 directory and run:

```bash
scons -j 4 build/RISCV/gem5.opt
```

## Example single-binary run

To execute individual binaries to test, in the ce challenge run folder, do the following:

For GAP benchmarks, to run bfs with uniform random graph for 10 iterations:

```bash
${GEM5_PATH}/build/RISCV/gem5.opt scripts/run-ce-challenge-GAP.py -b bfs -t g -g 4 -n 10

```

For TSVC benchmarks, to run s000 loop for 10 iterations:

```bash
${GEM5_PATH}/build/RISCV/gem5.opt scripts/run-ce-challenge-TSVC.py -b s000 -n 10

```

Make sure your binary path you want to execute is setup correctly in `env.sh`

