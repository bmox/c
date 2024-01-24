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


// @cloudshell:~$ cat << EOF > source.txt
// This is a sample text file created with cat.
// EOF
// @cloudshell:~$ nano cat_command.c 
// @cloudshell:~$ gcc cat_command.c -o cat_command
// @cloudshell:~$ ./cat_command source.txt
// This is a sample text file created with cat.