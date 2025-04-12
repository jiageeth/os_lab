#!/bin/bash

echo -n "Enter two numbers: "
read a b

echo -n "Enter choice (1: Sum, 2: Difference, 3: Product, 4: Quotient, 5: Remainder, 6: Exit): "
read ch

case $ch in
    1) echo "Sum: $((a + b))" ;;
    2) echo "Difference: $((a - b))" ;;
    3) echo "Product: $((a * b))" ;;
    4)
        if [ $b -ne 0 ]; then
            echo "Quotient: $((a / b))"
        else
            echo "Error: Division by zero"
        fi
        ;;
    5) echo "Remainder: $((a % b))" ;;
    6) echo "Exiting..."; exit ;;
    *) echo "Invalid choice" ;;
esac
