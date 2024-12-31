#!/bin/bash

find . -type f \( \
    -name "*.x" -o \
    -name "*.in" -o \
    -name "*.exe" \
\) -exec rm -f {} +