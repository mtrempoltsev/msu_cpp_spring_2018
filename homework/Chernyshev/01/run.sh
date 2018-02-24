#!/bin/bash

# Build project
make --silent clean
make --silent

# Run testing
./run_tests.sh sum_by_rows sum_by_cols

# Delete compiled programms
make --silent clean
