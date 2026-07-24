#!/bin/bash

echo "Enter first number:"
read num1
echo "Enter second number:"
read num2
echo "Enter operator (+, -, *, /):"
read op

if [ "$op" = "+" ]; then
    echo "Sum: $((num1 + num2))"
elif [ "$op" = "-" ]; then
    echo "Difference: $((num1 - num2))"
elif [ "$op" = "*" ]; then
    echo "Product: $((num1 * num2))"
elif [ "$op" = "/" ]; then
    if [ "$num2" -ne 0 ]; then
        echo "Quotient: $((num1 / num2))"
    else
        echo "Division by zero is not allowed."
    fi
else
    echo "Invalid operator."
fi
