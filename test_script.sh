#!/bin/bash

# Loop through t1 to t10
make
for i in {1..10}
do
    echo "test num ${i}"
    # Run the program with input from hw1-tests/tX.in and redirect the output to test_results/tX.res
    ./hw1 < "hw1-tests/t${i}.in" > "test_results/t${i}.res"

    # Compare the generated result with the expected output (tX.out) using diff
    diff "test_results/t${i}.res" "hw1-tests/t${i}.out"
done
