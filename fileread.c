#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main() {
    int fd = open("example.txt", O_CREAT | O_RDWR, 0666);
    if (fd < 0) {
        perror("File open error");
        return 1;
    }

    const char *text = "Hello, this is sample text";
    int len = strlen(text);

    // Write to the file
    write(fd, text, len);

    // Move file pointer to beginning
    lseek(fd, 0, SEEK_SET);

    // Read the content back
    char buffer[100];
    int bytesRead = read(fd, buffer, len);
    buffer[bytesRead] = '\0';  // Null-terminate the string

    // Print the content
    printf("File content: %s\n", buffer);

    // Close the file
    close(fd);
    return 0;
}
