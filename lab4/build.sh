#!/usr/bin/env bash

MY_CC="cc"
EXTRA_ARGS=""

which cc &> /dev/null

if [[ $? != "0" ]]; then 
    MY_CC="clang"
    EXTRA_ARGS="-Wno-deprecated-declarations"
fi

$MY_CC my_readline.c -o main.o -O3 -g $EXTRA_ARGS
