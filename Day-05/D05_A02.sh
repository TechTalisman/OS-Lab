#!/bin/bash

echo "Enter array elements separated by spaces:"
read -a arr

declare -A freq

for num in "${arr[@]}"; do
    ((freq[$num]++))
done

echo "Frequency of elements:"

for key in "${!freq[@]}"; do
    echo "$key: ${freq[$key]}"
done
