#!/bin/bash

mkdir -p build
cmake -G Ninja -S llvm -B build \ 
	-DCMAKE_BUILD_TYPE=Release \
	-DLLVM_TARGETS_TO_BUILD="RISCV;host" \
	-DLLVM_ENABLE_PROJECTS="clang;lld" \
	-DLLVM_DEFAULT_TARGET_TRIPLE="riscv64-unknown-linux-gnu" \
	-DDEFAULT_SYSROOT="/opt/riscv/sysroot" \
	-DLLVM_RUNTIME_TARGETS="riscv64-unknown-linux-gnu" \
	-DLLVM_PARALLEL_LINK_JOBS=4
cmake --build build -j $(nproc)
