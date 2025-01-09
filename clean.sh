#!/bin/bash

file_types=("*.x" "*.in" "*.out" "*.exe")

for ext in "${file_types[@]}"; do
    find . -type f -name "$ext" -exec rm -f {} \;
done

find . -type d -name ".cph" -exec rm -rf {} \;