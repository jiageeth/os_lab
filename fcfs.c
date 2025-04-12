#include <stdio.h>

int main() {
    int n, i, j, total = 0;
    int pid[10], at[10], bt[10], ct[10], tt[10], wt[10];
    int temp;
    float avg_wt = 0, avg_tt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter PID, Arrival Time and Burst Time for process %d: ", i + 1);
        scanf("%d %d %d", &pid[i], &at[i], &bt[i]);
    }

    // Sorting processes by arrival time
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                // Swap arrival time
                temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                // Swap burst time
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                // Swap PID
                temp = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp;
            }
        }
    }

    // FCFS Scheduling logic
    for (i = 0; i < n; i++) {
        if (total < at[i]) {
            total = at[i];  // CPU waits if the process hasn’t arrived
        }
        ct[i] = total + bt[i];   // Completion time
        total = ct[i];
        tt[i] = ct[i] - at[i];   // Turnaround time
        wt[i] = tt[i] - bt[i];   // Waiting time
        avg_wt += wt[i];
        avg_tt += tt[i];
    }

    // Output
    printf("\nPID\tARR\tBURST\tCOMP\tTURN\tWAIT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tt[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tt / n);

    return 0;
}