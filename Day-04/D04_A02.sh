#!/bin/bash

# Check if exactly three arguments are provided
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <num1> <operator> <num2>"
    echo "Supported operators: + - * / %"
    exit 1
fi

num1=$1
operator=$2
num2=$3

case "$operator" in
    +)
        echo "Result: $((num1 + num2))"
        ;;
    -)
        echo "Result: $((num1 - num2))"
        ;;
    \*)
        echo "Result: $((num1 * num2))"
        ;;
    /)
        if [ "$num2" -eq 0 ]; then
            echo "Error: Division by zero is not allowed."
        else
            echo "Result: $((num1 / num2))"
        fi
        ;;
    %)
        if [ "$num2" -eq 0 ]; then
            echo "Error: Modulus by zero is not allowed."
        else
            echo "Result: $((num1 % num2))"
        fi
        ;;
    *)
        echo "Error: Unsupported operator '$operator'."
        echo "Supported operators: + - * / %"
        exit 1
        ;;
esac
