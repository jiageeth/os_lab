#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

int main() {
    int pages[MAX_PAGES], frames[MAX_FRAMES];
    int n, f, i, j, k, pageFaults = 0, isHit;
    int frequency[MAX_FRAMES]; // To keep track of usage count

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

    // Initialize frames and frequency count
    for(i = 0; i < f; i++) {
        frames[i] = -1;       // -1 means empty frame
        frequency[i] = 0;     // Usage count starts at 0
    }

    // LFU Page Replacement Logic
    for(i = 0; i < n; i++) {
        isHit = 0;

        // Check if page is already in frame (Hit)
        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                isHit = 1;
                frequency[j]++; // Increase usage count
                break;
            }
        }

        // Page Fault (not in frames)
        if(isHit == 0) {
            int lfu = 0;

            // Find least frequently used page (minimum frequency)
            for(j = 1; j < f; j++) {
                if(frequency[j] < frequency[lfu])
                    lfu = j;
            }

            // Replace LFU page with current page
            frames[lfu] = pages[i];
            frequency[lfu] = 1;  // First usage of the new page
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
