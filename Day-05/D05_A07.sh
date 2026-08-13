#!/bin/bash

echo "Using Recursive Function for Fibonacci"

fib() {
    if [ "$1" -le 1 ]; then
        echo "$1"
    else
        echo $(( $(fib $(( $1 - 1 ))) + $(fib $(( $1 - 2 ))) ))
    fi
}

read -p "Enter the number of terms (n): " n

for ((i=0; i<n; i++)); do
    echo -n "$(fib "$i") "
done

echo

echo "Using Non-Recursive Function for Fibonacci"

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
        local next=$((a + b))
        echo -n "$next "
        a=$b
        b=$next
    done

    echo
}

read -p "Enter the number of terms (n): " n
fibonacci "$n"
