#!/usr/bin/env bash

MY_CC="cc"
ARGS="voters.c sort_type.c argparse.c main.c -o main -O3 -g"

which cc &> /dev/null

if [[ $? != "0" ]]; then
    echo "I did not find 'cc', so using 'clang' instead"
    MY_CC="clang"
    ARGS="$ARGS -Wno-deprecated-declarations"
fi

if [[ $1 == "1" ]]; then
    ARGS="$ARGS -lreadline -D PROGRAM_ID=1"
fi

COMMAND="$MY_CC $ARGS"

printf "Running '$COMMAND'\n\n"

$COMMAND
