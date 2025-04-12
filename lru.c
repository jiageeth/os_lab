#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

int main() {
    int pages[MAX_PAGES], frames[MAX_FRAMES];
    int n, f, i, j, k, pageFaults = 0, isHit;
    int recent[MAX_FRAMES]; // To keep track of last used time
    int time = 0;

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

    // Initialize frames and recent usage
    for(i = 0; i < f; i++) {
        frames[i] = -1;    // -1 means empty frame
        recent[i] = 0;     // No usage yet
    }

    // LRU Page Replacement Logic
    for(i = 0; i < n; i++) {
        isHit = 0;

        // Check if page is already in frame (Hit)
        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                isHit = 1;
                recent[j] = time++; // Update last used time
                break;
            }
        }

        // Page Fault (not in frames)
        if(isHit == 0) {
            int lru = 0;
            // Find least recently used page (minimum recent time)
            for(j = 1; j < f; j++) {
                if(recent[j] < recent[lru])
                    lru = j;
            }

            // Replace LRU page with current page
            frames[lru] = pages[i];
            recent[lru] = time++;  // Update last used time
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