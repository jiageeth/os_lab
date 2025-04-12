#include <stdio.h>

int main() {
    int n, i, j;
    int id[100], at[100], bt[100], ct[100], wt[100], tt[100];
    int remaining_bt[100];
    int temp;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input process details
    for(i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time, and Burst Time for process %d: ", i + 1);
        scanf("%d%d%d", &id[i], &at[i], &bt[i]);
        remaining_bt[i] = bt[i];  // Copy burst time into remaining time
    }

    // Sort processes by arrival time
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(at[j] > at[j + 1]) {
                // Swap all values
                temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;
                
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;
                
                temp = remaining_bt[j];
                remaining_bt[j] = remaining_bt[j + 1];
                remaining_bt[j + 1] = temp;
                
                temp = id[j];
                id[j] = id[j + 1]; 
                id[j + 1] = temp;
            }
        }
    }

    int time = 0, completed = 0;

    while(completed < n) {
        int min_index = -1;
        int min_bt = 10000; // A large value

        // Find the process with the smallest remaining burst time that has arrived
        for(i = 0; i < n; i++) {
            if(at[i] <= time && remaining_bt[i] > 0 && remaining_bt[i] < min_bt) {
                min_bt = remaining_bt[i];
                min_index = i;
            }
        }

        if(min_index != -1) {
            remaining_bt[min_index]--; // Execute for 1 unit of time
            time++; // Move time forward

            if(remaining_bt[min_index] == 0) {
                ct[min_index] = time; // Completion time
                tt[min_index] = ct[min_index] - at[min_index]; // Turnaround time
                wt[min_index] = tt[min_index] - bt[min_index]; // Waiting time
                completed++;
            }
        } else {
            time++; // If no process is ready, just increment time
        }
    }

    // Output results
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for(i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", id[i], at[i], bt[i], ct[i], tt[i], wt[i]);
    }

    return 0;
}
