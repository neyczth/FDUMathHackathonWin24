#!/bin/bash

find . -type f \( \
    -name "*.x" -o \
    -name "*.in" -o \
    -name "*.exe" -o \
    -name "*.out" \
\) -delete

find . -type d -name ".cph" -exec rm -rf {} +