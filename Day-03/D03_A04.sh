#!/bin/bash

total=0
subjects=5

echo "Enter the marks for $subjects subjects out of 100:"
for ((i = 1; i <= subjects; i++)); do
  read -p "Subject $i: " mark
  
  while [[ $mark -lt 0 || $mark -gt 100 ]]; do
    echo "Invalid input. Marks should be between 0 and 100."
    read -p "Subject $i: " mark
  done
  total=$((total + mark))
done

percentage=$((total / subjects))

if [ $percentage -ge 90 ]; then
  grade="A"
  message="Congratulations! You have achieved Distinction."
elif [ $percentage -ge 75 ]; then
  grade="B"
  message="Well done! You have performed very well."
elif [ $percentage -ge 50 ]; then
  grade="C"
  message="Good effort! Keep working to improve further."
else
  grade="F"
  message="Unfortunately, you have failed. Better luck next time."
fi

echo ""
echo "--- Result ---"
echo "Total Marks: $total/500"
echo "Percentage: $percentage%"
echo "Grade: $grade"
echo "$message"
