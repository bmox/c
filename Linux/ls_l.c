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


// @cloudshell:~$ echo "This is a sentence for file1." > file1.txt
// echo "This is a sentence for file2." > file2.txt
// echo "This is a sentence for file3." > file3.txt
// @cloudshell:~$ nano ls_l_command.c
// @cloudshell:~$ gcc ls_l_command.c -o ls_l_command
// @cloudshell:~$ ./ls_l_command ./
// -rw-r--r-- 1 cloudshell cloudshell 2592 Jan 24 11:11 ls_l_command.c
// -rw-r--r-- 1 cloudshell cloudshell 30 Jan 24 11:10 file3.txt
// -rw-r--r-- 1 cloudshell cloudshell 30 Jan 24 11:10 file2.txt
// -rwxr-xr-x 1 cloudshell cloudshell 17264 Jan 24 11:11 ls_l_command
// -rw-r--r-- 1 cloudshell cloudshell 30 Jan 24 11:10 file1.txt