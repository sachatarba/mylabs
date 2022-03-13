#!/bin/bash

gcc --std=c99 -Wall -Werror -Wpedantic -Wextra  -o main.exe ../../main.c -lm

counter=1
for file in ../data/pos*in.txt; do
    if [[ -f $file ]]; then
        ./main.exe < $file > out.txt
        out_file="../data/pos_0"
        out_file+="$counter"
        out_file+="_out.txt"
        if diff out.txt $out_file; then
            echo "$file: passed"
        else
            echo "$file: failed"
        fi
        counter=$(($counter + 1))
    fi
done

counter=1
for file in ../data/neg*in.txt; do
    if [[ -f $file ]]; then
        ./main.exe < $file > out.txt
        out_file="../data/neg_0"
        out_file+="$counter"
        out_file+="_out.txt"
        if diff out.txt $out_file; then
            echo "$file: passed"
        else
            echo "$file: failed"
        fi
        counter=$(($counter + 1))
    fi
done


rm -f out.txt main.exe