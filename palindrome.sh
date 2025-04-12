#!/bin/bash

echo "Palindrome numbers between $1 and $2:"

for (( i=$1; i<=$2; i++ ))
do
    rev=$(echo $i | rev)
    if [ $i -eq $rev ]; then
        echo $i
    fi
done
