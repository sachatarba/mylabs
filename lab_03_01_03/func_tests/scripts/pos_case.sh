#!/bin/bash

file_in=$1
file_expected_out=$2
file_args=$3

if [[ -f $file_args ]]; then
    args=$(cat "$file_args")
fi

if [ -z "$(printenv USE_VALGRIND)" ]; then
    if ../../app.exe "$args" < "$file_in" > file_out.txt; then
        if ./comparator.sh "$file_expected_out" file_out.txt; then
            exit 0
        else
            exit 1
        fi
    else
        exit 1
    fi
else
    if valgrind ../../app.exe "$args" < "$file_in" > file_out.txt; then
        if ./comparator.sh "$file_expected_out" file_out.txt; then
            exit 0
        else
            exit 1
        fi
    else
        exit 1
    fi
fi
