#!/bin/bash

echo "Enter the number of units consumed:"
read units

if [ "$units" -le 100 ]; then
    bill=$(awk "BEGIN {print $units * 1.50}")
elif [ "$units" -le 300 ]; then
    bill=$(awk "BEGIN {print (100 * 1.50) + (($units - 100) * 2.50)}")
else
    bill=$(awk "BEGIN {print (100 * 1.50) + (200 * 2.50) + (($units - 300) * 4.00)}")
fi

if (( $(awk "BEGIN {print ($bill > 1000)}") )); then
    surcharge=$(awk "BEGIN {print $bill * 0.10}")
else
    surcharge=0
fi

total=$(awk "BEGIN {print $bill + $surcharge}")

echo
echo "--- Electricity Bill ---"
echo "Units Consumed : $units"
printf "Basic Bill     : ₹%.2f\n" "$bill"
printf "Surcharge      : ₹%.2f\n" "$surcharge"
printf "Total Bill     : ₹%.2f\n" "$total"
