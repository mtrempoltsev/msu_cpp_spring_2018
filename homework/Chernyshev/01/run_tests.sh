#!/bin/bash

# Number of tests for warming up and testing
num_tests_warm_up=2
num_tests=5

# Start testing for each argument
for file
do
    # Warming up
    for (( i = 0; i < num_tests_warm_up; ++i ))
    do
        ./"$file" &> /dev/null
    done


    # Testing
    sum=0
    for (( i = 0; i < num_tests; ++i ))
    do
        cur=$( ./"$file" 2> /dev/null )
        sum=$(( sum + cur ))
    done

    # Print results
    awk "BEGIN {printf(\"Time for $file: %.5gs\n\", $sum / $num_tests / 1000 / 1000)}"
done
