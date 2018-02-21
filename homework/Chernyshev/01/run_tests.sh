#!/bin/bash

# Build project
make clean
make

echo ""

# Run testing
./run.sh sum_by_rows sum_by_cols

