LLVM_INSTALL_PATH=../llvm/build/bin
CXX = $(LLVM_INSTALL_PATH)/clang
OPT = $(LLVM_INSTALL_PATH)/opt
LLC = $(LLVM_INSTALL_PATH)/llc
LD = $(LLVM_INSTALL_PATH)/ld.lld
CXX_OPT_FLAGS = -O3 -static -Wall
CXX_FLAGS =  -static -Wall -target riscv64-linux-gnu -march=rv64gcv -Wl,-rpath=/opt/riscv/sysroot/lib -L/opt/riscv/sysroot/lib -I/opt/riscv/sysroot/include --sysroot=/opt/riscv/sysroot -fuse-ld=${LD}


##########################
# User optimization flag #
##########################
OPT_FLAGS =


LOOPS = s000 s121 s131 s171 s1213 s2244 s251 s1281 s311 s351 s491 s442 s212 s222 s231 s281 s13110 s332 s341 s352 s4114 s321
BINS = $(patsubst %, build/%, $(LOOPS))


.PHONY: all
all: build $(BINS) bin

build :
	mkdir -p build

bin :
	mkdir -p bin
	cp $(BINS) bin/

.PRECIOUS: build/tsc_%.o
build/tsc_%.o : tsc.c dummy.inc types.h
	$(CXX) $(CXX_OPT_FLAGS) -DLOOP$* -c $< -o $@

.PRECIOUS: build/%.ll
build/%.ll : loops/%.c common.h
	$(CXX) $(CXX_OPT_FLAGS) -S -emit-llvm $< -o $@

.PRECIOUS: build/%.opt.ll
build/%.opt.ll : build/%.ll
	$(OPT) $(OPT_FLAGS) -S $< -o $@

.PRECIOUS: build/%.o
build/%.o : build/%.opt.ll
	$(LLC) -filetype=obj $< -o $@

build/% : build/%.o build/tsc_%.o
	$(CXX) $(CXX_FLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf bin build tsc.o
