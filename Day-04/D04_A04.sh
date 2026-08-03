#!/bin/bash

read -p "Enter the value of n: " n

# Validate input
if [ "$n" -lt 0 ]; then
    echo "Error: Please enter a non-negative number."
    exit 1
fi

a=0
b=1

echo "Fibonacci numbers less than or equal to $n:"

while [ "$a" -le "$n" ]; do
    echo -n "$a "
    temp=$((a + b))
    a=$b
    b=$temp
done

echo
