#include <stdio.h>

int max[10][10], allocation[10][10], need[10][10];
int avail[10];
int np, nr;

// Function to read matrix input
void readmatrix(int matrix[10][10]) {
    for (int i = 0; i < np; i++)
        for (int j = 0; j < nr; j++)
            scanf("%d", &matrix[i][j]);
}

// Function to display a matrix
void display_matrix(int matrix[10][10]) {
    for (int i = 0; i < np; i++) {
        printf("\n P%d", i);
        for (int j = 0; j < nr; j++) {
            printf("  %d", matrix[i][j]);
        }
    }
    printf("\n");
}

// Function to calculate the need matrix
void calculate_need() {
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nr; j++) {
            need[i][j] = max[i][j] - allocation[i][j]; // Need = Max - Allocation
        }
    }
}

// Function to check the system's safe sequence
void banker() {
    int i, j, k = 0, flag;
    int finish[10], safe_seq[10];

    for (i = 0; i < np; i++)
        finish[i] = 0;

    while (1) {
        flag = 0;
        for (i = 0; i < np; i++) {
            if (finish[i] == 0) {
                int canExecute = 1;
                for (j = 0; j < nr; j++) {
                    if (need[i][j] > avail[j]) {
                        canExecute = 0;
                        break;
                    }
                }
                if (canExecute) {
                    finish[i] = 1;
                    safe_seq[k++] = i;
                    for (j = 0; j < nr; j++)
                        avail[j] += allocation[i][j];

                    flag = 1;
                }
            }
        }
        if (flag == 0)
            break;
    }

    if (k == np) {
        printf("\nThe system is in a safe state!\nSafe sequence is: ");
        for (i = 0; i < k; i++)
            printf(" P%d", safe_seq[i]);
        printf("\n");
    } else {
        printf("\nThe system is in deadlock\n");
    }
}

// Function to process a resource request
void request_resources(int process_id, int request[]) {
    int j;

    // Step 1: Check if request exceeds need
    for (j = 0; j < nr; j++) {
        if (request[j] > need[process_id][j]) {
            printf("\nError: Process P%d requested more than its need.\n", process_id);
            return;
        }
    }

    // Step 2: Check if resources are available
    for (j = 0; j < nr; j++) {
        if (request[j] > avail[j]) {
            printf("\nProcess P%d must wait, not enough resources available.\n", process_id);
            return;
        }
    }

    // Step 3: Try allocating temporarily
    for (j = 0; j < nr; j++) {
        avail[j] -= request[j];
        allocation[process_id][j] += request[j];
        need[process_id][j] -= request[j];
    }

    // Step 4: Check for safety
    banker();

    // Step 5: Grant or rollback
    int safe = 1;
    for (j = 0; j < nr; j++) {
        if (need[process_id][j] > avail[j]) {
            safe = 0;
            break;
        }
    }

    if (safe) {
        printf("\nRequest granted to Process P%d.\n", process_id);
    } else {
        printf("\nRequest cannot be granted, rolling back.\n");
        for (j = 0; j < nr; j++) {
            avail[j] += request[j];
            allocation[process_id][j] -= request[j];
            need[process_id][j] += request[j];
        }
    }
}

int main() {
    int process_id, request[10];

    printf("Enter the number of processes: ");
    scanf("%d", &np);
    printf("Enter number of resources: ");
    scanf("%d", &nr);

    printf("Enter the initial allocation matrix:\n");
    readmatrix(allocation);

    printf("Enter the Max requirement matrix:\n");
    readmatrix(max);

    printf("Enter available resources:\n");
    for (int i = 0; i < nr; i++) {
        scanf("%d", &avail[i]);
    }

    calculate_need();

    printf("\n****** Entered Data ******\n");
    printf("\nInitial Allocation:\n");
    display_matrix(allocation);

    printf("\nMaximum Requirement:\n");
    display_matrix(max);

    printf("\nAvailable Resources:\n");
    for (int j = 0; j < nr; j++)
        printf("%d ", avail[j]);

    printf("\n\nNeed Matrix:\n");
    display_matrix(need);

    // Allow the user to make a resource request
    printf("\nDo you want to make a resource request? (1-Yes, 0-No): ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter process ID making the request: ");
        scanf("%d", &process_id);

        printf("Enter resource request for process P%d: ", process_id);
        for (int i = 0; i < nr; i++) {
            scanf("%d", &request[i]);
        }

        request_resources(process_id, request);
    }

    // Run Banker's Algorithm to check final system state
    banker();

    return 0;
}