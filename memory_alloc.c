#include <stdio.h>
//about the process
struct process {
    int id;
    int psize;
    int blkno;
} p[10];

//about the memoryblock
struct block {
    int id;
    int bsize;
    int allc;
} b[10], temp;

//firstfit
void fristfit(int m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (b[j].allc == -1 && b[j].bsize >= p[i].psize) {
                p[i].blkno = b[j].id;
                b[j].allc = 1;
                break;
            }
        }
    }
    // Printing 
    printf("\nProcess ID\tProcess Size\tBlock No\n");
    for (int i = 0; i < n; i++) {
        if (p[i].blkno != -1)
            printf("%d\t\t%d\t\t%d\n", p[i].id, p[i].psize, p[i].blkno);
        else
            printf("%d\t\t%d\t\tNot Allocated\n", p[i].id, p[i].psize);
    }
}
//BEST FIT
void bestfit(int m, int n) {
    // Sort based on block size
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - i - 1; j++) {
            if (b[j].bsize > b[j + 1].bsize) {
                temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (b[j].allc == -1 && b[j].bsize >= p[i].psize) {
                p[i].blkno = b[j].id;
                b[j].allc = 1;
                break;
            }
        }
    }
    // Printing 
    printf("\nProcess ID\tProcess Size\tBlock No\n");
    for (int i = 0; i < n; i++) {
        if (p[i].blkno != -1)
            printf("%d\t\t%d\t\t%d\n", p[i].id, p[i].psize, p[i].blkno);
        else
            printf("%d\t\t%d\t\tNot Allocated\n", p[i].id, p[i].psize);
    }
}

void worstfit(int m, int n) {
    // Sort blocks in descending order of size
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - i - 1; j++) {
            if (b[j].bsize < b[j + 1].bsize) {
                temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
        }
    }

    // Allocate blocks using Worst Fit strategy
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (b[j].allc == -1 && b[j].bsize >= p[i].psize) {
                p[i].blkno = b[j].id;
                b[j].allc = 1;
                break;
            }
        }
    }

    // Printing the allocation results
    printf("\nProcess ID\tProcess Size\tBlock No\n");
    for (int i = 0; i < n; i++) {
        if (p[i].blkno != -1)
            printf("%d\t\t%d\t\t%d\n", p[i].id, p[i].psize, p[i].blkno);
        else
            printf("%d\t\t%d\t\tNot Allocated\n", p[i].id, p[i].psize);
    }
}

void calculateInternalFragmentation(int m, int n) {
    int totalInternalFragmentation = 0;
    for (int i = 0; i < n; i++) {
        if (p[i].blkno != -1) {
            for (int j = 0; j < m; j++) {
                if (b[j].id == p[i].blkno) {
                    totalInternalFragmentation += b[j].bsize - p[i].psize;
                    break;
                }
            }
        }
    }
    printf("Total Internal Fragmentation: %d\n", totalInternalFragmentation);
}

void calculateExternalFragmentation(int m, int n) {
    int totalExternalFragmentation = 0;
    for (int i = 0; i < m; i++) {
        if (b[i].allc == -1) {
            totalExternalFragmentation += b[i].bsize;
        }
    }
    printf("Total External Fragmentation: %d\n", totalExternalFragmentation);
}

int main() {
    int m, n;
    printf("Enter the no of memory blocks: ");
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        printf("Enter the block id and size %d: ", i + 1);
        scanf("%d%d", &b[i].id, &b[i].bsize);
        b[i].allc = -1;
    }

    printf("Enter the no of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter the process id and size %d: ", i + 1);
        scanf("%d%d", &p[i].id, &p[i].psize);
        p[i].blkno = -1;
    }

    // Reset allocation flags and process allocation before each algorithm
    for (int i = 0; i < m; i++) b[i].allc = -1;
    for (int i = 0; i < n; i++) p[i].blkno = -1;
    fristfit(m, n);
    calculateInternalFragmentation(m, n);
    calculateExternalFragmentation(m, n);

    for (int i = 0; i < m; i++) b[i].allc = -1;
    for (int i = 0; i < n; i++) p[i].blkno = -1;
    bestfit(m, n);
    calculateInternalFragmentation(m, n);
    calculateExternalFragmentation(m, n);

    for (int i = 0; i < m; i++) b[i].allc = -1;
    for (int i = 0; i < n; i++) p[i].blkno = -1;
    worstfit(m, n);
    calculateInternalFragmentation(m, n);
    calculateExternalFragmentation(m, n);

    return 0;
}