#!/bin/bash
echo "Script Name: $0"

echo "Number of Arguments: $#"

index=1
for arg in "$@"; do
  echo "Argument $index: $arg"
  index=$((index + 1))
done
