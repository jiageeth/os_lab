#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int range, req, requests[50], head;
    int q1[50], q2[50], queue[100];
    int k1 = 0, k2 = 0, t = 0;
    long long int seek = 0;

    printf("Enter the max range of the disk: ");
    scanf("%d", &range);

    printf("Enter the number of requests: ");
    scanf("%d", &req);

    printf("Enter the disk positions to be read:\n");
    for (int i = 0; i < req; i++)
        scanf("%d", &requests[i]);

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    // Split into two queues: one >= head, one < head
    for (int i = 0; i < req; i++) {
        if (requests[i] >= head)
            q2[k2++] = requests[i];
        else
            q1[k1++] = requests[i];
    }

    // Sort q2 in ascending
    for (int i = 0; i < k2 - 1; i++) {
        for (int j = 0; j < k2 - i - 1; j++) {
            if (q2[j] > q2[j + 1]) {
                int temp = q2[j];
                q2[j] = q2[j + 1];
                q2[j + 1] = temp;
            }
        }
    }

    // Sort q1 in descending
    for (int i = 0; i < k1 - 1; i++) {
        for (int j = 0; j < k1 - i - 1; j++) {
            if (q1[j] > q1[j + 1]) {
                int temp = q1[j];
                q1[j] = q1[j + 1];
                q1[j + 1] = temp;
            }
        }
    }

    // Form full queue: head → q2 (upward) → range → q1 (downward)
    queue[t++] = head;
    for (int i = 0; i < k2; i++)
        queue[t++] = q2[i];

    queue[t++] = range;
    for (int i = 0; i < k1; i++)
        queue[t++] = q1[i];

    // Calculate seek time
    for (int i = 0; i < t - 1; i++) {
        int diff = abs(queue[i + 1] - queue[i]);
        seek += diff;
        printf("Move from %d to %d: Seek = %d\n", queue[i], queue[i + 1], diff);
    }

    printf("\nTotal Seek Time = %lld\n", seek);
    return 0;
}
