#!/bin/bash

gcc -c main.c -Wall -Werror -Wpedantic -Wextra -g3
gcc -o app.exe main.o -lm
