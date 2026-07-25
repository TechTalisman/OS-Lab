#!/bin/bash

num1=14
num2=25

if [ "$num1" -eq "$num2" ]; then
    echo "Assigned numbers are equal."
else
    echo "Assigned numbers are not equal."
fi

echo "Enter the first number:"
read input1

echo "Enter the second number:"
read input2

if [ "$input1" -eq "$input2" ]; then
    echo "Entered numbers are equal."
else
    echo "Entered numbers are not equal."
fi
