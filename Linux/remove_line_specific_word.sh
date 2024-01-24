# Write a shell script that deletes all lines containing a
# specified word in one or more files specified as arguments to it.

#!/bin/bash

# Check if correct number of arguments are provided
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <word_to_remove> <file1> [<file2> ...]"
    exit 1
fi

word_to_remove="$1"
shift

# Iterate through each file and remove the lines containing the specified word
for file in "$@"; do
    # Check if the file exists
    if [ ! -e "$file" ]; then
        echo "File not found: $file"
        continue
    fi

    # Remove lines containing the word from the file
    sed -i "/\b$word_to_remove\b/d" "$file"

    echo "Lines containing the word removed from $file"
done

# @cloudshell:~$ nano sample.txt
# @cloudshell:~$ nano file1.txt
# @cloudshell:~$ cat sample.txt
# How are you?
# okay
# @cloudshell:~$ cat file1.txt
# How are you?
# okay
# @cloudshell:~$ nano remove.sh
# @cloudshell:~$ chmod +x remove.sh
# @cloudshell:~$ ./remove.sh "okay" file1.txt sample.txt
# Lines containing the word removed from file1.txt
# Lines containing the word removed from sample.txt
# @cloudshell:~$ cat file1.txt
# How are you?