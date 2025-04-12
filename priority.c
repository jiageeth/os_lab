#include <stdio.h>

int main() 
{
    int n, i, j;
    int id[100], at[100], bt[100], pr[100];
    int ct[100], tt[100], wt[100];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input for all processes
    for(i = 0; i < n; i++) 
    {
        printf("Enter Process ID, Arrival Time, Burst Time, and Priority (lower number = higher priority) for process %d: ", i + 1);
        scanf("%d %d %d %d", &id[i], &at[i], &bt[i], &pr[i]);
    }

    // Sort processes by priority (lower number = higher priority) using bubble sort
    for(i = 0; i < n - 1; i++) 
    {
        for(j = 0; j < n - i - 1; j++) 
        {
            if(pr[j] > pr[j + 1])
            {
                // Swap priority
                int temp = pr[j];
                pr[j] = pr[j + 1];
                pr[j + 1] = temp;

                // Swap burst time
                temp = bt[j];
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
    ct[0] = at[0] + bt[0];  // First process completes after it arrives and finishes

    for(i = 1; i < n; i++) 
    {
        if(ct[i - 1] > at[i]) 
        {
            // If previous process completed after this one arrived, wait and then add burst time
            ct[i] = ct[i - 1] + bt[i];
        }
    else 
    {
        // If this process arrived after the last one finished, start it at arrival time
        ct[i] = at[i] + bt[i];
    }
    }


    // Calculate Turnaround Time and Waiting Time
    for(i = 0; i < n; i++)
    {
        tt[i] = ct[i] - at[i];
        wt[i] = tt[i] - bt[i];
    }

    // Display the results
    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for(i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", id[i], at[i], bt[i], pr[i], ct[i], tt[i], wt[i]);
    }

    return 0;
}

