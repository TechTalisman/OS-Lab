#!/bin/bash

fibonacci() {
    local n=$1
    local a=0
    local b=1

    if [ "$n" -le 0 ]; then
        return
    fi

    echo -n "$a "

    if [ "$n" -eq 1 ]; then
        echo
        return
    fi

    echo -n "$b "

    for ((i=2; i<n; i++)); do
        fib=$((a + b))
        echo -n "$fib "
        a=$b
        b=$fib
    done

    echo
}

read -p "Enter the value of n: " n
fibonacci "$n"
