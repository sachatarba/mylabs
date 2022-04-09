#!/bin/bash

gcc -c main.c -Wall -Werror -Wpedantic -Wextra -g
gcc -o app.exe main.o -lm
