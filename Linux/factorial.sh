#!/bin/bash

# Function to calculate factorial
calculate_factorial() {
    if [ "$1" -le 1 ]; then
        echo 1
    else
        echo $(( $1 * $(calculate_factorial $(( $1 - 1 ))) ))
    fi
}

# Check if an argument is provided
if [ "$#" -eq 0 ]; then
    echo "Usage: $0 <number>"
    exit 1
fi

# Get the number from the command-line argument
number=$1

# Check if the number is a non-negative integer
if [[ ! "$number" =~ ^[0-9]+$ ]]; then
    echo "Error: Please provide a non-negative integer."
    exit 1
fi

# Calculate and print the factorial
result=$(calculate_factorial $number)
echo "Factorial of $number is: $result"


# @cloudshell:~$ nano fact.sh
# @cloudshell:~$ chmod +x fact.sh
# @cloudshell:~$ ./fact.sh 5
# Factorial of 5 is: 120