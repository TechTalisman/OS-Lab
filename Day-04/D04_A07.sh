#!/bin/bash

read -p "Enter the starting number of the range: " start
read -p "Enter the ending number of the range: " end

# Validate input
if [ "$start" -lt 2 ] || [ "$end" -lt "$start" ]; then
    echo "Error: Please enter a valid range starting from 2."
    exit 1
fi

echo "Prime numbers in the range $start to $end:"

for ((num = start; num <= end; num++)); do
    is_prime=1

    for ((i = 2; i * i <= num; i++)); do
        if ((num % i == 0)); then
            is_prime=0
            break
        fi
    done

    case "$is_prime" in
        1)
            echo "$num is a prime number."
            ;;
        0)
            echo "$num is not a prime number."
            ;;
    esac
done
