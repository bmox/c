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


// @cloudshell:~$ cat << EOF > source.txt
// This is a sample text file.
// EOF
// @cloudshell:~$ nano copy_file.c
// @cloudshell:~$ gcc copy_file.c -o copy_file
// @cloudshell:~$ ./copy_file source.txt destination.txt
// File copy successful: source.txt -> destination.txt