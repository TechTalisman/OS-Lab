#!/bin/bash

echo "Enter first number:"
read num1

echo "Enter second number:"
read num2

echo "Two numbers are: $num1 and $num2"

echo "Sum: $((num1 + num2))"
echo "Difference: $((num1 - num2))"
echo "Product: $((num1 * num2))"

if [ "$num2" -ne 0 ]; then
    echo "Quotient: $((num1 / num2))"
else
    echo "Division by zero is not allowed."
fi
