#!/bin/bash

PROGRAM="./volsort"
INPUT="input"

# Function to run the program and use the built-in 'time' for basic timing
run_time() {
    echo "Running: $@"
    { time "$@"; } 2>&1 | tee output.log
    echo
}

# Test with different flags and configurations
echo "Testing time for different sort methods and flags..."

# Test stl string
run_time $PROGRAM -m stl < $INPUT

# Test stl number
run_time $PROGRAM -m stl -n < $INPUT

# Test qsort string
run_time $PROGRAM -m qsort < $INPUT

# Test qsort number
run_time $PROGRAM -m qsort -n < $INPUT

# Test merge string
run_time $PROGRAM -m merge < $INPUT

# Test merge number
run_time $PROGRAM -m merge -n < $INPUT

# Test quick string
run_time $PROGRAM -m quick < $INPUT

# Test quick number
run_time $PROGRAM -m quick -n < $INPUT

echo "Time tests complete."

