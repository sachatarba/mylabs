#!/bin/bash

gcc --std=c99 -Wall -Werror -Wpedantic -Wextra -o main.exe ../../main.c

counter=1
for file in ../data/*in.txt; do
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

rm -f out.txt main.exe