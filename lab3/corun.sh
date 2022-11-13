#!/usr/bin/env bash

cc rational.c commands.c main.c -o main.o -O3 -g && ./main.o
