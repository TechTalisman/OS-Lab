#!/bin/bash

echo "Enter array elements separated by spaces:"
read -a arr

reversed=()

for ((i=${#arr[@]}-1; i>=0; i--)); do
    reversed+=("${arr[$i]}")
done

echo "Reversed Array: ${reversed[*]}"
