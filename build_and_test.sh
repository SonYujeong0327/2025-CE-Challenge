#!/bin/bash

# Build LLVM
cd llvm && ./llvm_build.sh

# Build gem5
cd ../gem5 && scons -j$(nproc) build/RISCV/gem5.opt

# Build tsvc
cd ../tsvc && make clean && make

# Build gapbs
cd ../gapbs && make clean && make

# Run test
cd ../ce_challenge_2025 && source env.sh && ./RUN_SELF_TEST

# Return to base directory
cd ../
