#include <stdio.h>

int main() {
    int n, i, j;
    int id[100], at[100], bt[100];
    int ct[100], tt[100], wt[100];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input process details
    for(i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time, and Burst Time for process %d: ", i + 1);
        scanf("%d %d %d", &id[i], &at[i], &bt[i]);
    }

    // Sort processes based on burst time using Bubble Sort
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(bt[j] > bt[j + 1]) {
                // Swap burst time
                int temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                // Swap arrival time
                temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                // Swap process ID
                temp = id[j];
                id[j] = id[j + 1];
                id[j + 1] = temp;
            }
        }
    }

    // Calculate Completion Time
    ct[0] = at[0] + bt[0];
    for(i = 1; i < n; i++) {
        if(ct[i - 1] < at[i])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i - 1] + bt[i];
    }

    // Calculate Turnaround Time and Waiting Time
    for(i = 0; i < n; i++) {
        tt[i] = ct[i] - at[i];
        wt[i] = tt[i] - bt[i];
    }

    // Print the results
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for(i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", id[i], at[i], bt[i], ct[i], tt[i], wt[i]);
    }

    return 0;
}
