#!/bin/bash

echo "Enter array elements separated by spaces:"
read -a arr

sorted=($(printf "%s\n" "${arr[@]}" | sort -n | uniq))

if [ "${#sorted[@]}" -lt 2 ]; then
    echo "Not enough unique elements in the array."
else
    echo "Second Smallest: ${sorted[1]}"
    echo "Second Largest: ${sorted[${#sorted[@]}-2]}"
fi
