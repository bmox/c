# a.Create 5 empty files, empty1, empty 2, empty 3, empty is empty 5
```
google@cloudshell:~/test$ touch empty1 empty2 empty3 empty4 empty5

google@cloudshell:~/test$ ls

empty1  empty2  empty3  empty4  empty5
```
# b. Create a text file and store name, age, sex & address in it.
```
google@cloudshell:~/test$ vim personal_info.txt 

me: John Doe

Age: 30

Sex: Male

Address: 123 Main Street, Usa

Esc and  :wq for save and exit

google@cloudshell:~/test$ ls

 personal_info.txt
```

# C. display the file content on the screen 
```
google@cloudshell:~/test$ cat  personal_info.txt

me: John Doe

Age: 30

Sex: Male

Address: 123 Main Street, Usa
```

# d. Make a copy of the fill content into another text file.
```
google@cloudshell:~/test$ cat personal_info.txt > copied_info.txt

google@cloudshell:~/test$ cat copied_info.txt

me: John Doe

Age: 30

Sex: Male

Address: 123 Main Street, Usa
```

# e. Create a file new.txt and write any sentence in it
```
google@cloudshell:~/test$ echo "This is a sample sentence." > new.txt

google@cloudshell:~/test$ echo "This is the second sentence." >> new.txt

google@cloudshell:~/test$ cat new.txt

This is a sample sentence.

This is the second sentence.
```

# f. Rename the file to new.txt to old.txt
```
google@cloudshell:~/test$ mv new.txt old.txt

google@cloudshell:~/test$ ls

old.txt
```
# g. create a new directory called mydir inside current directory
```
google@cloudshell:~/test$ ls

old.txt

google@cloudshell:~/test$ mkdir mydir

google@cloudshell:~/test$ ls

mydir  old.txt
```
# h. Move old.txt file inside new directory mydir
```
google@cloudshell:~/test$ mv old.txt mydir/

google@cloudshell:~/test$ ls

mydir

google@cloudshell:~/test$ cd mydir

google@cloudshell:~/test/mydir$ ls

old.txt
```

# i.Copy the content of mydir to newdir
```
google@cloudshell:~/test$ ls

mydir

google@cloudshell:~/test$ cp -r mydir newdir

google@cloudshell:~/test$ ls

mydir  newdir
```
# j. Details interactively all empty file

```
google@cloudshell:~/test$ ls

a.txt  mydir  newdir

google@cloudshell:~/test$ find . -type f -empty -exec stat {} \;

  File: ./a.txt

  Size: 0               Blocks: 0          IO Block: 4096   regular empty file

Device: 811h/2065d      Inode: 131258      Links: 1

Access: (0644/-rw-r--r--)  Uid: ( 1000/google)   Gid: ( 1000/google)

Access: 2023-10-07 13:27:04.051418605 +0000

Modify: 2023-10-07 13:27:04.051418605 +0000

Change: 2023-10-07 13:27:04.051418605 +0000

 Birth: 2023-10-07 13:27:04.051418605 +0000
```

# 4. Suppose the path exists in your directory. (dir1/dir2/dir3/dir4) all these directories are empty. How do you remove all of them in one command****
```
google@cloudshell:~/test/dir1/dir2/dir3/dir4$ pwd

/home/google/test/dir1/dir2/dir3/dir4

google@cloudshell:~/test$ ls

dir1

google@cloudshell:~/test$ rm -rf dir1

google@cloudshell:~/test$ ls
```
# write a shell script that accepts the file name starting and ending the numbers as arguments and display all the lines between the given line numbers
### Code
```
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

```
### Output
```
@cloudshell:~$ ls
a.txt
@cloudshell:~$ cat a.txt
Hello
hi
are
you
?
@cloudshell:~$ nano display_lines.sh
@cloudshell:~$ ls
a.txt  display_lines.sh
@cloudshell:~$ chmod +x display_lines.sh
@cloudshell:~$ ./display_lines.sh a.txt 2 4
hi
are
you
```
### Write a shell script that deletes all lines containing a specified word in one or more files specified as arguments to it.

### Code
```
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


```
### Output:
```
@cloudshell:~$ nano sample.txt
@cloudshell:~$ nano file1.txt
@cloudshell:~$ cat sample.txt
How are you?
okay
@cloudshell:~$ cat file1.txt
How are you?
okay
@cloudshell:~$ nano remove.sh
@cloudshell:~$ chmod +x remove.sh
@cloudshell:~$ ./remove.sh "okay" file1.txt sample.txt
Lines containing the word removed from file1.txt
Lines containing the word removed from sample.txt
@cloudshell:~$ cat file1.txt
How are you?
```
# Write a shell script that displays a list of all the files in the current directory to which the user has read, write, and execute permissions.
### Code:
```
#!/bin/bash

# Display a list of files with read, write, and execute permissions for the user
echo "Files with read, write, and execute permissions for the user:"
echo "-----------------------------------------------------------"

for file in *; do
    if [ -f "$file" ] && [ -r "$file" ] && [ -w "$file" ] && [ -x "$file" ]; then
        echo "$file"
    fi
done

```

### Output:
```
@cloudshell:~$ echo "This is a test file." > test_file.txt
@cloudshell:~$ chmod u+rwx test_file.txt
@cloudshell:~$ nano list_files.sh
@cloudshell:~$ chmod +x list_files.sh
@cloudshell:~$ ls
file1.txt  file2.txt  file3.txt  list_files.sh  test_file.txt
@cloudshell:~$ ./list_files.sh
Files with read, write, and execute permissions for the user:
-----------------------------------------------------------
list_files.sh
test_file.txt

```
# Write a shell script that accepts a list of file names as its arguments. The script should count and report the occurrence of each word present in the first argument file within the other argument files. Create a script named word_occurrence.sh to achieve this task.
### Code
```
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

```
### Output:
```
@cloudshell:~$ # Create reference_file.txt
cat << EOF > reference_file.txt
apple orange banana
EOF

# Create file1.txt
cat << EOF > file1.txt
apple banana apple
EOF

# Create file2.txt
cat << EOF > file2.txt
orange apple
EOF

# Create file3.txt
cat << EOF > file3.txt
grape banana apple
EOF
@cloudshell:~$ nano word_occurrence.sh
@cloudshell:~$ chmod +x word_occurrence.sh
@cloudshell:~$ ./word_occurrence.sh reference_file.txt file1.txt file2.txt file3.txt
Word occurrences in 'file1.txt':
banana: 2 occurrences
orange: 1 occurrences
apple: 3 occurrences
---------------------------
Word occurrences in 'file2.txt':
banana: 1 occurrences
orange: 2 occurrences
apple: 2 occurrences
---------------------------
Word occurrences in 'file3.txt':
banana: 2 occurrences
grape: 1 occurrences
orange: 1 occurrences
apple: 2 occurrences
---------------------------
```
# write a shell script to print factorial of a given number 
### Code:
```
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

```
### Output:
```
@cloudshell:~$ nano fact.sh
@cloudshell:~$ chmod +x fact.sh
@cloudshell:~$ ./fact.sh 5
Factorial of 5 is: 120
```

# write a AWK script to find the number of characters, words and lines in a text file.
### Code:
```
#!/usr/bin/awk -f

{
    # Count characters
    char_count += length

    # Count words
    word_count += NF

    # Count lines
    line_count++
}

END {
    print "Number of characters: " char_count
    print "Number of words: " word_count
    print "Number of lines: " line_count
}

```
### Output:
```
@cloudshell:~$
cat << EOF > example.txt
This is a sample text file.
It has multiple lines for testing.
Feel free to add more content.
EOF
@cloudshell:~$ nano run.awk
@cloudshell:~$ chmod +x run.awk
@cloudshell:~$ ./run.awk example.txt
Number of characters: 91
Number of words: 18
Number of lines: 3
```
# Write a C program that creates a copy of a given file using a combination of standard I/O functions and system calls. The program should take the names of the source file and the destination file as command-line arguments and perform the copy operation.
### Code:
```
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    FILE *source_file, *destination_file;
    char buffer[BUFFER_SIZE];
    size_t bytes_read, bytes_written;

    // Check if the correct number of command-line arguments is provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the source file for reading
    source_file = fopen(argv[1], "rb");
    if (source_file == NULL) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open the destination file for writing
    destination_file = fopen(argv[2], "wb");
    if (destination_file == NULL) {
        perror("Error opening destination file");
        fclose(source_file);
        exit(EXIT_FAILURE);
    }

    // Copy data from source to destination using standard I/O functions
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        bytes_written = fwrite(buffer, 1, bytes_read, destination_file);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            fclose(source_file);
            fclose(destination_file);
            exit(EXIT_FAILURE);
        }
    }

    // Close the files
    fclose(source_file);
    fclose(destination_file);

    printf("File copy successful: %s -> %s\n", argv[1], argv[2]);

    return 0;
}

```
### Output:
```
@cloudshell:~$ cat << EOF > source.txt
This is a sample text file.
EOF
@cloudshell:~$ nano copy_file.c
@cloudshell:~$ gcc copy_file.c -o copy_file
@cloudshell:~$ ./copy_file source.txt destination.txt
File copy successful: source.txt -> destination.txt
```

#   Implement in C the following UNIX commands using system calls A) cat  B) MV 
### cat_command.c
```
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char ch;

    // Check if the correct number of command-line arguments is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the file for reading
    file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Display the contents of the file to standard output
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    // Close the file
    fclose(file);

    return 0;
}

```
### mv_command.c
```
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_filename> <destination_filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Rename the file using the rename system call
    if (rename(argv[1], argv[2]) != 0) {
        perror("Error renaming file");
        exit(EXIT_FAILURE);
    }

    printf("File moved successfully: %s -> %s\n", argv[1], argv[2]);

    return 0;
}

```
### Output:
```
@cloudshell:~$ cat << EOF > source.txt
This is a sample text file created with cat.
EOF
@cloudshell:~$ nano cat_command.c 
@cloudshell:~$ gcc cat_command.c -o cat_command
@cloudshell:~$ ./cat_command source.txt
This is a sample text file created with cat.
@cloudshell:~$ nano mv_command.c
@cloudshell:~$ gcc mv_command.c -o mv_command
@cloudshell:~$ ls
cat_command  cat_command.c  mv_command  mv_command.c  source.txt
@cloudshell:~$ ./mv_command source.txt dest.txt
File moved successfully: source.txt -> dest.txt
@cloudshell:~$ cat dest.txt
This is a sample text file created with cat.
```
#
### ls_l_command.c
```
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_file_info(struct stat *file_stat, char *file_name) {
    // Display file type and permissions
    printf((S_ISDIR(file_stat->st_mode)) ? "d" : "-");
    printf((file_stat->st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat->st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat->st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat->st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat->st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat->st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat->st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat->st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat->st_mode & S_IXOTH) ? "x" : "-");

    // Display number of hard links
    printf(" %lu", file_stat->st_nlink);

    // Display owner and group
    struct passwd *pw = getpwuid(file_stat->st_uid);
    struct group *gr = getgrgid(file_stat->st_gid);
    printf(" %s %s", pw->pw_name, gr->gr_name);

    // Display size of the file
    printf(" %ld", file_stat->st_size);

    // Display modification time
    char time_buffer[50];
    strftime(time_buffer, sizeof(time_buffer), "%b %d %H:%M", localtime(&file_stat->st_mtime));
    printf(" %s", time_buffer);

    // Display file name
    printf(" %s\n", file_name);
}

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    // Set the directory path based on command-line argument
    char *directory_path = (argc > 1) ? argv[1] : ".";

    // Open the directory
    dir = opendir(directory_path);
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    // Read and display information about each file in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Construct the full path of the file
        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", directory_path, entry->d_name);

        // Get information about the file
        if (stat(full_path, &file_stat) != 0) {
            perror("Error getting file information");
            closedir(dir);
            exit(EXIT_FAILURE);
        }

        // Skip entries for the current directory and parent directory
        if (entry->d_name[0] == '.')
            continue;

        // Print detailed information about the file
        print_file_info(&file_stat, entry->d_name);
    }

    // Close the directory
    closedir(dir);

    return 0;
}

```
### Output:
```
@cloudshell:~$ echo "This is a sentence for file1." > file1.txt
echo "This is a sentence for file2." > file2.txt
echo "This is a sentence for file3." > file3.txt
@cloudshell:~$ nano ls_l_command.c
@cloudshell:~$ gcc ls_l_command.c -o ls_l_command
@cloudshell:~$ ./ls_l_command ./
-rw-r--r-- 1 cloudshell cloudshell 2592 Jan 24 11:11 ls_l_command.c
-rw-r--r-- 1 cloudshell cloudshell 30 Jan 24 11:10 file3.txt
-rw-r--r-- 1 cloudshell cloudshell 30 Jan 24 11:10 file2.txt
-rwxr-xr-x 1 cloudshell cloudshell 17264 Jan 24 11:11 ls_l_command
-rw-r--r-- 1 cloudshell cloudshell 30 Jan 24 11:10 file1.txt
```
