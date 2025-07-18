# 2025 CE Challenge

The main objectives of Computer Engineering (CE) Challenge 2025 are to analyze and improve the branch prediction mechanism of the RISC-V architecture and to strengthen the vectorization capabilites of the LLVM compiler.

Detailed submission rules are described in https://cechallenge.github.io/


## Getting Started

Please read and follow these instructions carefully.

### 1. Fork this repository

**Fork** this repository into your github account as a **private** repository.

Do **NOT directly clone** this repository.


### 2. Clone your repository

**Clone** your forked repository into your local server. 

We haven't tested MacOS/Windows environment, so we highly recommend to use a Linux-based server.

```
git clone https://github.com/[your_github_id]/2025
```

### 3. Pull docker image

(TO BE UPDATED)


### 4. Run docker image

(TO BE UPDATED)


### 5. Run build and test

To run end-to-end build and test script, go to the repository and run the script in docker:
```
cd [path_to_repo]
bash build_and_test.sh
```

## Build and Test

This section describes sperated steps of `build_and_test.sh`. You can seperately build and test each directory.

### Build LLVM

```
cd llvm && ./llvm_build.sh
```
### Build gem5
```
cd gem5 && scons -j$(nproc) build/RISCV/gem5.opt
```
### Build tsvc
```
cd tsvc && make clean && make
```
### Build gapbs
```
cd gapbs && make clean && make
```
### Run test
`ce_challenge_2025` directory contains testing environment. Refer [ce_challenge_2025/README.md](https://github.com/cechallenge/2025/blob/main/ce_challenge_2025/README.md) for details.
```
cd ce_challenge_2025 && source env.sh && ./RUN_SELF_TEST
```
