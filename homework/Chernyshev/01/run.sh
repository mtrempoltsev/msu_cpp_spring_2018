#!/bin/bash

# Number of tests for warming up and testing
num_tests_warm_up=2
num_tests=5

# Start testing for each argument
for file
do
    sum=0

    # Warming up
    for i in {1..num_tests_warm_up}
    do
        ./"$file" &> /dev/null
    done

    # Testing
    for i in {1..num_tests}
    do
        cur=$( ./"$file" 2> /dev/null )
        sum=$(( sum + cur ))
    done

    # Print results
    echo "Time for $file: "$(( sum / num_tests ))"ms"
done
