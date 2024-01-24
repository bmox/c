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
// @cloudshell:~$ cat << EOF > source.txt
// This is a sample text file created with cat.
// EOF
// @cloudshell:~$ nano mv_command.c
// @cloudshell:~$ gcc mv_command.c -o mv_command
// @cloudshell:~$ ls
// cat_command  cat_command.c  mv_command  mv_command.c  source.txt
// @cloudshell:~$ ./mv_command source.txt dest.txt
// File moved successfully: source.txt -> dest.txt
// @cloudshell:~$ cat dest.txt
// This is a sample text file created with cat.