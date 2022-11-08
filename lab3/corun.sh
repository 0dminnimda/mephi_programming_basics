#!/usr/bin/env bash

cc -c commands.c && cc commands.o main.c -o main.o -lm -O3 && ./main.o
