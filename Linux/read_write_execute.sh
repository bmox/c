# Write a shell script that displays a list of all the files
# in the current directory to which the user has read, write,
# and execute permissions.

#!/bin/bash

# Display a list of files with read, write, and execute permissions for the user
echo "Files with read, write, and execute permissions for the user:"
echo "-----------------------------------------------------------"

for file in *; do
    if [ -f "$file" ] && [ -r "$file" ] && [ -w "$file" ] && [ -x "$file" ]; then
        echo "$file"
    fi
done

# @cloudshell:~$ echo "This is a test file." > test_file.txt
# @cloudshell:~$ chmod u+rwx test_file.txt
# @cloudshell:~$ nano list_files.sh
# @cloudshell:~$ chmod +x list_files.sh
# @cloudshell:~$ ls
# file1.txt  file2.txt  file3.txt  list_files.sh  test_file.txt
# @cloudshell:~$ ./list_files.sh
# Files with read, write, and execute permissions for the user:
# -----------------------------------------------------------
# list_files.sh
# test_file.txt
