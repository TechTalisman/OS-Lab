#!/bin/bash

# Function to list files/directories with read and write permissions
list_rw() {
    echo "Files/Directories with read and write permissions:"
    
    for item in *; do
        if [ -r "$item" ] && [ -w "$item" ]; then
            echo "$item"
        fi
    done
}

list_rw
