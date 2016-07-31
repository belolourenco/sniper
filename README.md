# SNIPER

## Overview

[**SNIPER**](https://github.com/lamraoui/sniper) (SNIPER is Not an Imperative
Errors Repairer) is a tool to automatically localize faults in imperative
programs, such as the ones written in ANSI C. SNIPER makes use of the LLVM
compiler infrastructure for processing input programs, and uses Yices 1 as a
backend SMT solver. The architecture of SNIPER is based on the LLVM compiler
infrastructure to facilitate the handling of programs to be analyzed.

**SNIPER** can also be viewed as a framework on top of what it is possible to
implement various backends. For example, in the current version, **SNIPER**
implements a backend to automatically localize faults (see SniperBackend).
Other methods to analyze computer programs can be implemented as well, without
much effort.

**SNIPER-VCGen** is an extension of SNIPER used to generate Verification
Conditions (VCs) using different Verification Condition Generators (VCGens).
The tool takes as input a source program (normally C code) compiles it into
the LLVM-IR, applies a series of transformations to the intermediate
representation and uses a VCGen to generate a set of VCs. These VCs can then
be sent directly to the
[YICES](http://yices.csl.sri.com/old/download-yices1.shtml) solver to check
their satisfiability or else they can be used to generate an [SMT-LIB
v2](http://smtlib.cs.uiowa.edu/) file which can later be sent to
[Z3](https://github.com/Z3Prover/z3), [MathSAT](http://mathsat.fbk.eu/) or
[CVC4](http://cvc4.cs.nyu.edu/web/).

For more information about SNIPER-VCGen check
[here](http://alfa.di.uminho.pt/~belolourenco/sniper-vcgen/sniper-vcgen.html).

## Installation

The instructions for installing SNIPER-VCGen are the same as for installing
SNIPER. Refer to [SNIPER repository](https://github.com/lamraoui/sniper) for details.

## Using SNIPER-VCGen

The SNIPER-VCGen can be executed by command line as follows:

> `$ clang file.c -S -emit-llvm -O0 -gline-tables-only -o file.bc`

> `$ ./sniper -vcgen -function=f -cfile=file.c -unroll=10 -method=1 file.bc`

For additional information run:

> `$ ./sniper --help`

For executing the benchmarks run:

> `$ ./run_benchmarks`

## Licence

**SNIPER** and **SNIPER-VCGen** are open source software. You may freely distribute it under the terms of
the license agreement found in LICENSE.txt.