#include <stdio.h>

int main() {
    int n, quantum;
    int i, time = 0, completed = 0;
    int front = 0, rear = -1;

    int id[100], at[100], bt[100], ct[100], tt[100], wt[100];
    int remaining_bt[100], queue[100];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    for(i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time, and Burst Time for process %d: ", i + 1);
        scanf("%d %d %d", &id[i], &at[i], &bt[i]);
        remaining_bt[i] = bt[i]; // initialize remaining burst time
    }

    while(completed < n) 
    {
        // Add all newly arrived and not finished processes to queue
        for(i = 0; i < n; i++) {
            if(at[i] <= time && remaining_bt[i] > 0) {
                int already_in_queue = 0;
                // Check if already in queue
                for(int k = front; k <= rear; k++) 
                {
                    if(queue[k] == i) {
                        already_in_queue = 1;
                        break;
                    }
                }
                if(!already_in_queue) 
                {
                    queue[++rear] = i;
                }
            }
        }

        if(front <= rear) 
        {
            int processIndex = queue[front++];

            if(remaining_bt[processIndex] <= quantum) 
            {
                time += remaining_bt[processIndex];
                remaining_bt[processIndex] = 0;
                ct[processIndex] = time;
                tt[processIndex] = ct[processIndex] - at[processIndex];
                wt[processIndex] = tt[processIndex] - bt[processIndex];
                completed++;
            } else {
                time += quantum;
                remaining_bt[processIndex] -= quantum;

                // Re-add to queue
                queue[++rear] = processIndex;
            }
        } else 
        {
            time++; // No process is ready at this time
        }
    }

    // Display the results
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for(i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", id[i], at[i], bt[i], ct[i], tt[i], wt[i]);
    }

    return 0;
}

