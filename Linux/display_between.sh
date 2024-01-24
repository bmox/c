# write a shell script that accepts the file name starting and 
# ending the numbers as arguments and display all the lines between 
# the given line numbers

#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <file_name> <start_line_number> <end_line_number>"
    exit 1
fi

file_name="$1"
start_line="$2"
end_line="$3"

# Check if the file exists
if [ ! -e "$file_name" ]; then
    echo "Error: File '$file_name' not found."
    exit 1
fi

# Check if start and end line numbers are positive integers
if ! [[ "$start_line" =~ ^[0-9]+$ ]] || ! [[ "$end_line" =~ ^[0-9]+$ ]]; then
    echo "Error: Start and end line numbers must be positive integers."
    exit 1
fi

# Check if start line number is less than or equal to end line number
if [ "$start_line" -gt "$end_line" ]; then
    echo "Error: Start line number must be less than or equal to end line number."
    exit 1
fi

# Display lines between start and end line numbers
sed -n "${start_line},${end_line}p" "$file_name"


# @cloudshell:~$ ls
# a.txt
# @cloudshell:~$ cat a.txt
# Hello
# hi
# are
# you
# ?
# @cloudshell:~$ nano display_lines.sh
# @cloudshell:~$ ls
# a.txt  display_lines.sh
# @cloudshell:~$ chmod +x display_lines.sh
# @cloudshell:~$ ./display_lines.sh a.txt 2 4
# hi
# are
# you