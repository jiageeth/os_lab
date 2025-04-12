#!/bin/bash


echo "Enter the value of N"
read n   # 'n' is the number of terms in the Fibonacci sequence
a=0
b=1
echo "The Fibonacci series is:"

for ((i = 0; i < n; i++))
do
  echo "$a"
  fn=$((a + b))
  a=$b
  b=$fn
done
