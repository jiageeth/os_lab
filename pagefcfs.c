#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

int main() {
    int pages[MAX_PAGES], frames[MAX_FRAMES];
    int n, f, i, j, k, pageFaults = 0, isHit;
    int nextToReplace = 0;  // FCFS uses this pointer

    // Input number of pages
    printf("Enter number of pages: ");
    scanf("%d", &n);

    // Input page reference string
    printf("Enter the page reference string:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input number of frames
    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames
    for(i = 0; i < f; i++) {
        frames[i] = -1;    // -1 means empty frame
    }

    // FCFS Page Replacement Logic
    for(i = 0; i < n; i++) {
        isHit = 0;

        // Check if page is already in frame (Hit)
        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                isHit = 1;
                break;
            }
        }

        // Page Fault
        if(isHit == 0) {
            frames[nextToReplace] = pages[i];
            nextToReplace = (nextToReplace + 1) % f;  // Move to next frame in FCFS order
            pageFaults++;

            // Print current frame content
            printf("Page %d inserted -> [ ", pages[i]);
            for(k = 0; k < f; k++) {
                if(frames[k] != -1)
                    printf("%d ", frames[k]);
                else
                    printf("- ");
            }
            printf("]\n");
        }
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    return 0;
}

