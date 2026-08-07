#!/bin/bash

echo "Enter sorted array 1 elements separated by spaces:"
read -a arr1

echo "Enter sorted array 2 elements separated by spaces:"
read -a arr2

i=0
j=0
merged=()

while [ "$i" -lt "${#arr1[@]}" ] && [ "$j" -lt "${#arr2[@]}" ]; do
    if [ "${arr1[$i]}" -le "${arr2[$j]}" ]; then
        merged+=("${arr1[$i]}")
        ((i++))
    else
        merged+=("${arr2[$j]}")
        ((j++))
    fi
done

while [ "$i" -lt "${#arr1[@]}" ]; do
    merged+=("${arr1[$i]}")
    ((i++))
done

while [ "$j" -lt "${#arr2[@]}" ]; do
    merged+=("${arr2[$j]}")
    ((j++))
done

echo "Merged Sorted Array: ${merged[*]}"
