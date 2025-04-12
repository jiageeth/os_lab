#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        printf("Fork failed\n");
        exit(-1);
    }
    else if (pid == 0) {
        // Child process
        printf("Child process:\n");
        execl("./ADD", "ADD", "10", "20", NULL);
        exit(0);
    }
    else {
        // Parent process
        wait(NULL);
        printf("Child terminated\n");
        exit(0);
    }

    return 0;
}

