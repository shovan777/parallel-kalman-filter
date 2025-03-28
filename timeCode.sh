#!/bin/bash

# This script is used to time the parallelkalman execution
# Usage: ./timeCode.sh

# setup time variable
time=0
# Run for ten times
for i in {1..10}
do
    # capture the time required to compute the matrix multiplication
    # from the output
    i_time=$(./build/parallelkalman | grep "Time" | awk '{print $4}')
    echo "Time for $i th serial version: $i_time microseconds"
    time=$(echo "scale=6; $time+$i_time" | bc)

done

# calculate the average time
time=$(echo "scale=6; $time/10" | bc)
echo "Average time for serial version: $time microseconds"