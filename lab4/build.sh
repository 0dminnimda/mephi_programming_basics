#!/usr/bin/env bash

MY_CC="cc"
EXTRA_ARGS=""

which cc &> /dev/null

if [[ $? != "0" ]]; then
    echo "I did not find 'cc', so using 'clang' instead"
    MY_CC="clang"
    EXTRA_ARGS="$EXTRA_ARGS -Wno-deprecated-declarations"
fi

if [[ $1 == "1" ]]; then
    EXTRA_ARGS="$EXTRA_ARGS -lreadline -D PROGRAM_ID=1"
else
    EXTRA_ARGS="$EXTRA_ARGS my_string.c my_readline.c"
fi

COMMAND="$MY_CC alphabet.c words.c main.c -o main.o -O3 -g $EXTRA_ARGS"

printf "Running '$COMMAND'\n\n"

$COMMAND
