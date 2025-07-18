![GAP logo](https://scottbeamer.net/images/gap-logo-horiz.svg)

GAP Benchmark Suite [![Build Status](https://github.com/sbeamer/gapbs/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/sbeamer/gapbs/actions/workflows/c-cpp.yml)
===================

This is the reference implementation for the [GAP](http://gap.cs.berkeley.edu/) [Benchmark Suite](http://gap.cs.berkeley.edu/benchmark.html). It is designed to be a portable high-performance baseline that only requires a compiler with support for C++11. It uses OpenMP for parallelism, but it can be compiled without OpenMP to run serially. The details of the benchmark can be found in the [specification](http://arxiv.org/abs/1508.03619).

The GAP Benchmark Suite is intended to help graph processing research by standardizing evaluations. Fewer differences between graph processing evaluations will make it easier to compare different research efforts and quantify improvements. The benchmark not only specifies graph kernels, input graphs, and evaluation methodologies, but it also provides an optimized baseline implementation (this repo). These baseline implementations are representative of state-of-the-art performance, and thus new contributions should outperform them to demonstrate an improvement.

Kernels Included
----------------
+ Breadth-First Search (BFS) - direction optimizing
+ Single-Source Shortest Paths (SSSP) - delta stepping
+ PageRank (PR) - iterative method in pull direction, Gauss-Seidel & Jacobi
+ Connected Components (CC) - Afforest & Shiloach-Vishkin
+ Betweenness Centrality (BC) - Brandes
+ Triangle Counting (TC) - order invariant with possible degree relabelling


Quick Start
-----------

Build the project:

    $ make

Override the default C++ compiler:

    $ CXX=g++-13 make


Run BFS on 1,024 vertices for 1 iteration:

    $ ./bfs -g 10 -n 1

Additional command line flags can be found with `-h`


Graph Loading
-------------

All of the binaries use the same command-line options for loading graphs:
+ `-g 20` generates a Kronecker graph with 2^20 vertices (Graph500 specifications)
+ `-u 20` generates a uniform random graph with 2^20 vertices (degree 16)
+ `-f graph.el` loads graph from file graph.el
+ `-sf graph.el` symmetrizes graph loaded from file graph.el


How to Cite
-----------

Please cite this code by the benchmark specification:

> Scott Beamer, Krste Asanović, David Patterson. [*The GAP Benchmark Suite*](http://arxiv.org/abs/1508.03619). arXiv:1508.03619 [cs.DC], 2015.


To Learn More
-------------
The [specification](http://arxiv.org/abs/1508.03619) (above) provides the most detailed description of the benchmark and the reference implementation. The benchmark kernels were selected by a thorough methodology including an extensive literature search [2] and a detailed workload characterization [3]. In 2020, the leading shared-memory graph frameworks competed according to the GAP Benchmark specifications [1].

1. Ariful Azad, Mohsen Mahmoudi Aznaveh, Scott Beamer, et al. [*Evaluation of Graph Analytics Frameworks Using the GAP Benchmark Suite*](https://ieeexplore.ieee.org/document/9251247). International Symposium on Workload Characterization (IISWC), October 2020.

2. Scott Beamer. [*Understanding and Improving Graph Algorithm Performance*](https://www2.eecs.berkeley.edu/Pubs/TechRpts/2016/EECS-2016-153.html). PhD Thesis, University of California Berkeley, September 2016. _SPEC Kaivalya Dixit Distinguished Dissertation Award_.

3. Scott Beamer, Krste Asanović, David Patterson. [*Locality Exists in Graph Processing: Workload Characterization on an Ivy Bridge Server*](https://ieeexplore.ieee.org/document/7314147). International Symposium on Workload Characterization (IISWC), October 2015. _Best Paper Award_.
