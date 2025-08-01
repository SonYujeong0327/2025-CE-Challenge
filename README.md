# 2025 CE Challenge

The main objectives of Computer Engineering (CE) Challenge 2025 are to analyze and improve the branch prediction mechanism of the RISC-V architecture and to strengthen the vectorization capabilites of the LLVM compiler.

Detailed rules are described in https://cechallenge.github.io/


## Getting Started

Please read and follow these instructions carefully.


### 1. Clone repository

Clone this repository into your local server. 

We haven't tested MacOS/Windows environment, so we highly recommend to use a Linux-based server.

```
git clone https://github.com/cechallenge/2025 [your-local-repo]
```

### 2. Set up your private repository

First, make your own private repository on Github.

Second, **change** the `origin` remote to **your private Github repository**.

```
cd [your-local-repo]
git remote set-url origin https://github.com/[your-username]/[your-github-repo].git
```


Third, in your Github repository, add [@cechallenge](https://github.com/cechallenge) official Github account as a collaborator.

Please follow the [instructions](https://cechallenge.github.io/submission/) to submit your artifacts to the leaderboard.

### 3. Pull docker image

To locally test your artifact, pull the docker image first.
```
docker pull ghcr.io/cechallenge/ce_challenge_2025
```

### 4. Run docker image

Run the docker.
```
docker run -it -v [your-local-repo]:[path-to-docker-repo] ghcr.io/cechallenge/ce_challenge_2025:latest
```

### 5. Run build and test

To run end-to-end build and test script, go to the repository and run the script in docker:
```
cd [path-to-docker-repo]
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
