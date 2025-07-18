LLVM_INSTALL_PATH=../llvm/build/bin
CXX = $(LLVM_INSTALL_PATH)/clang++
OPT = $(LLVM_INSTALL_PATH)/opt
LLC = $(LLVM_INSTALL_PATH)/llc
LD = $(LLVM_INSTALL_PATH)/ld.lld
CXX_OPT_FLAGS = -O3 -fno-vectorize -fno-slp-vectorize -static -std=c++11 -Wall 
CXX_FLAGS =  -static -std=c++11 -Wall -target riscv64-linux-gnu -march=rv64gcv -Wl,-rpath=/opt/riscv/sysroot/lib -L/opt/riscv/sysroot/lib -I/opt/riscv/sysroot/include --sysroot=/opt/riscv/sysroot -fuse-ld=${LD}

##########################
# User optimization flag #
##########################
OPT_FLAGS = 


KERNELS = bc bfs cc cc_sv pr pr_spmv sssp tc
BINS = $(patsubst %, build/%, $(KERNELS))

.PHONY: all
all: build $(BINS) bin

build :
	mkdir -p build

bin :
	mkdir -p bin
	cp $(BINS) bin/


build/%.ll : src/%.cc src/*.h
	$(CXX) $(CXX_OPT_FLAGS) -S -emit-llvm $< -o $@

build/%.opt.ll : build/%.ll
	$(OPT) $(OPT_FLAGS) -S $< -o $@

build/%.o : build/%.opt.ll
	$(LLC) -filetype=obj $< -o $@

build/% : build/%.o
	$(CXX) $(CXX_FLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f test/out/*
	rm -rf bin build
