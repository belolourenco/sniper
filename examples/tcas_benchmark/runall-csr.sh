#!/bin/bash

# runall-time.sh
#
# ----------------------------------------------------------------------
#
# Experiment for SNIPER on the TCAS Benchmark
#
# This experiment aims at comparing the code size reduction (CSR) 
# obtained with SNIPER with different trace formula encodings.
#
# ----------------------------------------------------------------------
#                SNIPER : Automatic Fault Localization 
#
# Copyright (C) 2016 Si-Mohamed LAMRAOUI
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program (see LICENSE.TXT).  
# If not, see <http://www.gnu.org/licenses/>.
# ----------------------------------------------------------------------
#
# \author Si-Mohamed LAMRAOUI
# \date   31 March 2016


# Granularity level: -inst, -line, -block.
GRANU_LEVEL=-line


# Run SNIPER
function run {
    if [ "$2" == "HFTF" ]; then
        ENCODING=-htf
    fi
    echo ""
    echo "< $1 >"
    clang-mp-3.3 $1 -S -emit-llvm -O0 -gline-tables-only -o $1.bc >error 2>&1
    ./../../src/sniper -mhs -loc=173 -ce $GRANU_LEVEL $ENCODING -function foo -cfile $1 -ts testcases-argok.txt -go golden-outputs.txt $1.bc
    rm $1.bc
}

# Run SNIPER with Hardened Flow-sensitive Trace Formula (HFTF)
function runHFTF {
    run $1 $2 "HFTF"
}

# Run SNIPER with Full Flow-sensitive Trace Formula (FFTF)
function runFFTF {
    run $1 $2 "FFTF" 
}

# Check if SNIPER binarie exists
if [ ! -f ../../src/sniper ]; then
    echo "SNIPER binarie not found!"
    exit 1
fi

# Run all programs for both types of formulas
echo "Experiment for SNIPER on the TCAS Benchmark."
echo ""
echo "Granularity level:" $GRANU_LEVEL
echo "Getting average code size reductions (ACSR) for each program..."
echo ""

echo "=== HFTF ==================================="
for i in $(eval echo {1..41})
do
    runHFTF v$i/tcas.c
done
echo ""
echo ""

echo "=== FFTF ==================================="
for i in $(eval echo {1..41})
do
    runFFTF v$i/tcas.c
done
echo ""
echo ""