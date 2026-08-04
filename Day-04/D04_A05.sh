#!/bin/bash

echo "Enter numbers separated by spaces:"
read -a numbers

echo "Choose sorting order:"
echo "a - Ascending"
echo "d - Descending"
read order

if [ "$order" = "a" ]; then
    sorted=($(printf "%s\n" "${numbers[@]}" | sort -n))
    echo "Sorted in Ascending Order: ${sorted[*]}"
elif [ "$order" = "d" ]; then
    sorted=($(printf "%s\n" "${numbers[@]}" | sort -nr))
    echo "Sorted in Descending Order: ${sorted[*]}"
else
    echo "Invalid option. Please enter 'a' or 'd'."
fi
