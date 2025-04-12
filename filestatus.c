
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    dir = opendir(".");
    if (dir == NULL) {
        printf("Error opening directory\n");
        return 1;
    }

    printf("Files and their stats:\n");

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &file_stat) == 0) {
            printf("Name: %s\n", entry->d_name);
            printf("Size: %ld bytes\n", file_stat.st_size);
            printf("Permissions: %o\n", file_stat.st_mode & 0777);
            printf("Last modified: %ld\n", file_stat.st_mtime);
            printf("----------------------------\n");
        } else {
            printf("Unable to get stats for %s\n", entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}

    dir = opendir(".");
    if (dir == NULL) {
        printf("Error opening directory\n");
        return 1;
    }

    printf("Files and their stats:\n");

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &file_stat) == 0) {
            printf("Name: %s\n", entry->d_name);
            printf("Size: %ld bytes\n", file_stat.st_size);
            printf("Permissions: %o\n", file_stat.st_mode & 0777);
            printf("Last modified: %ld\n", file_stat.st_mtime);
            printf("----------------------------\n");
        } else {
            printf("Unable to get stats for %s\n", entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}
