#!/bin/bash

echo "Enter the file or directory name:"
read input

if [ -e "$input" ]; then
    if [ -f "$input" ]; then
        
        echo "$input is a file."
        file_size=$(du -sh "$input" | cut -f1)
        echo "Size: $file_size"
        
        if [ -r "$input" ]; then
            echo "The file is readable."
        else
            echo "The file is not readable."
        fi
        
        if [ -w "$input" ]; then
            echo "The file is writable."
        else
            echo "The file is not writable."
        fi
        
        if [ -x "$input" ]; then
            echo "The file is executable."
        else
            echo "The file is not executable."
        fi
    elif [ -d "$input" ]; then
    
        echo "$input is a directory."
    
        echo "Files and directories in $input:"
        ls -l "$input"
        
        file_count=$(find "$input" -type f | wc -l)
        dir_count=$(find "$input" -type d | wc -l)
        
        echo "Number of files: $file_count"
        echo "Number of subdirectories: $((dir_count - 1))" 
    else
        echo "$input is neither a file nor a directory."
    fi
else
    echo "$input does not exist."
fi
