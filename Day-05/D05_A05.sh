#!/bin/bash

echo "Enter array elements separated by spaces:"
read -a arr

# Find the length of the array
length=${#arr[@]}

# Check for palindrome
is_palindrome=true

for ((i=0; i<length/2; i++)); do
    if [[ "${arr[$i]}" != "${arr[$((length-i-1))]}" ]]; then
        is_palindrome=false
        break
    fi
done

if $is_palindrome; then
    echo "The array is a palindrome."
else
    echo "The array is not a palindrome."
fi
