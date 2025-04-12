#include <stdio.h>
#include <stdlib.h>

int main() 
{
    int range, req, requests[50], head;
    int queue[51];
    long long int seek = 0;
    int diff;

    printf("\nEnter the max range of the disk: ");
    scanf("%d", &range);

    printf("\nEnter the number of requests: ");
    scanf("%d", &req);

    printf("\nEnter the disk positions to be read:\n");
    for (int i = 0; i < req; i++) 
    {
        scanf("%d", &requests[i]);
    }

    printf("\nEnter the initial head position: ");
    scanf("%d", &head);

    // Prepare the FCFS queue
    queue[0] = head;
    for (int i = 0; i < req; i++) 
    {
        queue[i + 1] = requests[i];
    }

    printf("\n--- FCFS Disk Scheduling ---\n");

    for (int i = 0; i < req; i++) 
    {
        diff = abs(queue[i + 1] - queue[i]);
        seek += diff;
        printf("\nDisk head moves from %d to %d with seek time %d", queue[i], queue[i + 1], diff);
    }

    printf("\n\nTotal seek time: %lld\n", seek);

    return 0;
}
