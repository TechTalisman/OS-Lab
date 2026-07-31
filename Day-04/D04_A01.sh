#!/bin/bash

# Function to calculate factorial
factorial() {
    local num=$1
    local fact=1

    for ((i=1; i<=num; i++)); do
        fact=$((fact * i))
    done

    echo "$fact"
}

# Function to calculate GCD (Euclidean Algorithm)
gcd() {
    local a=$1
    local b=$2

    while [ "$b" -ne 0 ]; do
        local temp=$b
        b=$((a % b))
        a=$temp
    done

    echo "$a"
}

# Function to calculate LCM
lcm() {
    local a=$1
    local b=$2
    local gcd_value

    gcd_value=$(gcd "$a" "$b")
    echo $((a * b / gcd_value))
}

while true; do
    echo
    echo "========== Advanced Calculator =========="
    echo "1. Addition"
    echo "2. Subtraction"
    echo "3. Multiplication"
    echo "4. Division"
    echo "5. Power"
    echo "6. Factorial"
    echo "7. GCD"
    echo "8. LCM"
    echo "9. Exit"
    echo "========================================="
    read -p "Enter your choice (1-9): " choice

    case "$choice" in
        1)
            read -p "Enter two numbers: " a b
            echo "Result: $((a + b))"
            ;;
        2)
            read -p "Enter two numbers: " a b
            echo "Result: $((a - b))"
            ;;
        3)
            read -p "Enter two numbers: " a b
            echo "Result: $((a * b))"
            ;;
        4)
            read -p "Enter two numbers: " a b
            if [ "$b" -eq 0 ]; then
                echo "Error: Division by zero is not allowed."
            else
                echo "Result: $((a / b))"
            fi
            ;;
        5)
            read -p "Enter base and exponent: " base exp
            echo "Result: $((base ** exp))"
            ;;
        6)
            read -p "Enter a number: " num
            if [ "$num" -lt 0 ]; then
                echo "Error: Factorial of a negative number is not defined."
            else
                echo "Result: $(factorial "$num")"
            fi
            ;;
        7)
            read -p "Enter two numbers: " a b
            echo "Result: $(gcd "$a" "$b")"
            ;;
        8)
            read -p "Enter two numbers: " a b
            echo "Result: $(lcm "$a" "$b")"
            ;;
        9)
            echo "Exiting..."
            break
            ;;
        *)
            echo "Invalid choice. Please enter a number between 1 and 9."
            ;;
    esac
done
