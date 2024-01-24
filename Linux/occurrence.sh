# Write a shell script that accepts a list of file names as its arguments.
# The script should count and report the occurrence of each word present
# in the first argument file within the other argument files.
# Create a script named word_occurrence.sh to achieve this task.

#!/bin/bash

# Check if at least two arguments are provided
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <file1> <file2> [<file3> ...]"
    exit 1
fi

# Store the first argument as the reference file
ref_file=$1
shift

# Check if the reference file exists
if [ ! -e "$ref_file" ]; then
    echo "Error: Reference file '$ref_file' not found."
    exit 1
fi

# Process each remaining file
for file in "$@"; do
    # Check if the current file exists
    if [ ! -e "$file" ]; then
        echo "Warning: File '$file' not found. Skipping."
        continue
    fi

    # Count and report word occurrences in the current file
    echo "Word occurrences in '$file':"
    awk '
    { 
        for(i=1; i<=NF; i++) {
            word_count[$i]++
        }
    }
    END {
        for (word in word_count) {
            print word ": " word_count[word] " occurrences"
        }
    }' "$file" "$ref_file"
    echo "---------------------------"
done


# @cloudshell:~$ # Create reference_file.txt
# cat << EOF > reference_file.txt
# apple orange banana
# EOF

# # Create file1.txt
# cat << EOF > file1.txt
# apple banana apple
# EOF

# # Create file2.txt
# cat << EOF > file2.txt
# orange apple
# EOF

# # Create file3.txt
# cat << EOF > file3.txt
# grape banana apple
# EOF
# @cloudshell:~$ nano word_occurrence.sh
# @cloudshell:~$ chmod +x word_occurrence.sh
# @cloudshell:~$ ./word_occurrence.sh reference_file.txt file1.txt file2.txt file3.txt
# Word occurrences in 'file1.txt':
# banana: 2 occurrences
# orange: 1 occurrences
# apple: 3 occurrences
# ---------------------------
# Word occurrences in 'file2.txt':
# banana: 1 occurrences
# orange: 2 occurrences
# apple: 2 occurrences
# ---------------------------
# Word occurrences in 'file3.txt':
# banana: 2 occurrences
# grape: 1 occurrences
# orange: 1 occurrences
# apple: 2 occurrences
# ---------------------------