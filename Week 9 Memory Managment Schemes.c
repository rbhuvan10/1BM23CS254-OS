#include <stdio.h>

#define MAX 10
void print(char *name, int alloc[], int n) {
    printf("\n%s Allocation:\n", name);
    for (int i = 0; i < n; i++) {
        if (alloc[i] == -1)
            printf("Process %d -> Not Allocated\n", i + 1);
        else
            printf("Process %d -> Block %d\n", i + 1, alloc[i] + 1);
    }
}

void firstFit(int blocks[], int m, int procs[], int n) {
    int alloc[MAX], b[MAX];
    for (int i = 0; i < m; i++) b[i] = blocks[i];
    for (int i = 0; i < n; i++) {
        alloc[i] = -1;
        for (int j = 0; j < m; j++) {
            if (b[j] >= procs[i]) {
                alloc[i] = j;
                b[j] = -1;  
                break;
            }
        }
    }
    print("First Fit", alloc, n);
}
void bestFit(int blocks[], int m, int procs[], int n) {
    int alloc[MAX], b[MAX];
    for (int i = 0; i < m; i++) b[i] = blocks[i];
    for (int i = 0; i < n; i++) {
        alloc[i] = -1;
        int best = -1;
        for (int j = 0; j < m; j++) {
            if (b[j] >= procs[i] && (best == -1 || b[j] < b[best]))
                best = j;
        }
        if (best != -1) {
            alloc[i] = best;
            b[best] = -1;  
        }
    }
    print("Best Fit", alloc, n);
}
void worstFit(int blocks[], int m, int procs[], int n) {
    int alloc[MAX], b[MAX];
    for (int i = 0; i < m; i++) b[i] = blocks[i];
    for (int i = 0; i < n; i++) {
        alloc[i] = -1;
        int worst = -1;
        for (int j = 0; j < m; j++) {
            if (b[j] >= procs[i] && (worst == -1 || b[j] > b[worst]))
                worst = j;
        }
        if (worst != -1) {
            alloc[i] = worst;
            b[worst] = -1;  
        }
    }
    print("Worst Fit", alloc, n);
}

int main() {
    int blocks[MAX], procs[MAX], m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter block sizes:\n");
    for (int i = 0; i < m; i++) scanf("%d", &blocks[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter process sizes:\n");
    for (int i = 0; i < n; i++) scanf("%d", &procs[i]);

    firstFit(blocks, m, procs, n);
    bestFit(blocks, m, procs, n);
    worstFit(blocks, m, procs, n);

    return 0;
}

Output:
Enter number of memory blocks: 5
Enter block sizes:
150 250 350 450 550 
Enter number of processes: 4
Enter process sizes:
200 300 400 500

First Fit Allocation:
Process 1 -> Block 2
Process 2 -> Block 3
Process 3 -> Block 4
Process 4 -> Block 5

Best Fit Allocation:
Process 1 -> Block 2
Process 2 -> Block 3
Process 3 -> Block 4
Process 4 -> Block 5

Worst Fit Allocation:
Process 1 -> Block 5
Process 2 -> Block 4
Process 3 -> Not Allocated
Process 4 -> Not Allocated

