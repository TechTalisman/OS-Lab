#!/bin/bash

# Directory to search (default: current directory)
directory=${1:-.}

txt_count=0
sh_count=0
jpg_count=0
other_count=0

for file in "$directory"/* "$directory"/.*; do
    # Skip . and ..
    [[ "$(basename "$file")" == "." || "$(basename "$file")" == ".." ]] && continue

    if [ -f "$file" ]; then
        case "${file##*.}" in
            txt)
                ((txt_count++))
                ;;
            sh)
                ((sh_count++))
                ;;
            jpg|jpeg)
                ((jpg_count++))
                ;;
            *)
                ((other_count++))
                ;;
        esac
    fi
done

echo "File type counts in directory '$directory':"
echo "Text files (.txt): $txt_count"
echo "Shell scripts (.sh): $sh_count"
echo "JPEG images (.jpg/.jpeg): $jpg_count"
echo "Other files: $other_count"
