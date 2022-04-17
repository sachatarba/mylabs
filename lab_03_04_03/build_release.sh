#!/bin/bash

gcc -c main.c -Wall -Werror -Wpedantic -Wextra
gcc -o app.exe main.o -lm
