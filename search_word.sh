#!/bin/bash

echo -n "Enter file name: "
read filename

if [ ! -f "$filename" ]; then
    echo "Error: File Not Found"
    exit 1
fi

echo "Enter word to search"
read word

count=$(grep -o -i -w "$word" "$filename" | wc -l)
echo "'$word' occurred $count times in '$filename'"
