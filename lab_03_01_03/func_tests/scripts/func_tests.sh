#!/bin/bash

for file_in in ../data/pos_*in.txt; do
    if [[ -f $file_in ]]; then
        for file_out in ../data/pos_*out.txt; do
            if [[ -f $file_out ]]; then
                if [[ ${file_in:12:2} -eq ${file_out:12:2} ]]; then 
                    if ./pos_case.sh "$file_in" "$file_out"; then
                        echo "$file_in: passed"
                    else
                        echo "$file_out: failed"
                    fi
                fi
            fi
        done
    fi
done


for file_in in ../data/neg_*in.txt; do
    if [[ -f $file_out ]]; then 
        if ./neg_case.sh "$file_in"; then
            echo "$file_in: passed"
        else
            echo "$file_in: failed"
        fi
    fi
done
