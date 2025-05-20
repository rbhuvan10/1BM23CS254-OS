#include <stdio.h>
#include <stdbool.h>

void print(int step, int frames, int mem[], bool fault) {
    printf("Step %d: ", step);
    for (int i = 0; i < frames; i++) printf("%d ", mem[i] == -1 ? -1 : mem[i]);
    printf("%s\n", fault ? " (Fault)" : "");
}

void fifo(int f, int len, int ref[]) {
    int mem[f], ptr = 0, faults = 0;
    for (int i = 0; i < f; i++) mem[i] = -1;

    for (int i = 0; i < len; i++) {
        bool hit = false;
        for (int j = 0; j < f; j++) if (mem[j] == ref[i]) hit = true;
        if (!hit) {
            mem[ptr] = ref[i];
            ptr = (ptr + 1) % f;
            faults++;
        }
        print(i + 1, f, mem, !hit);
    }
    printf("FIFO Faults: %d\n", faults);
}

void lru(int f, int len, int ref[]) {
    int mem[f], use[f], faults = 0;
    for (int i = 0; i < f; i++) mem[i] = use[i] = -1;

    for (int i = 0; i < len; i++) {
        bool hit = false;
        for (int j = 0; j < f; j++) {
            if (mem[j] == ref[i]) {
                use[j] = i;
                hit = true;
            }
        }
        if (!hit) {
            int lru = 0;
            for (int j = 1; j < f; j++) if (use[j] < use[lru]) lru = j;
            mem[lru] = ref[i];
            use[lru] = i;
            faults++;
        }
        print(i + 1, f, mem, !hit);
    }
    printf("LRU Faults: %d\n", faults);
}

void optimal(int f, int len, int ref[]) {
    int mem[f], faults = 0;
    for (int i = 0; i < f; i++) mem[i] = -1;

    for (int i = 0; i < len; i++) {
        bool hit = false;
        for (int j = 0; j < f; j++) if (mem[j] == ref[i]) hit = true;

        if (!hit) {
            int rep = -1, far = i;
            for (int j = 0; j < f; j++) {
                int k;
                for (k = i + 1; k < len; k++) if (mem[j] == ref[k]) break;
                if (k > far) { far = k; rep = j; }
                if (k == len) { rep = j; break; }
            }
            for (int j = 0; j < f; j++) if (mem[j] == -1) { rep = j; break; }
            mem[rep] = ref[i];
            faults++;
        }
        print(i + 1, f, mem, !hit);
    }
    printf("Optimal Faults: %d\n", faults);
}

int main() {
    int f, len;
    printf("Frames: "); scanf("%d", &f);
    printf("Ref string length: "); scanf("%d", &len);
    int ref[len];
    printf("Enter ref string: ");
    for (int i = 0; i < len; i++) scanf("%d", &ref[i]);

    printf("\nFIFO:\n"); fifo(f, len, ref);
    printf("\nLRU:\n"); lru(f, len, ref);
    printf("\nOptimal:\n"); optimal(f, len, ref);
    return 0;
}

Output:Frames: 3
Ref string length: 10
Enter ref string: 1 3 4 5 7 2 3 4 5 4

FIFO:
Step 1: 1 -1 -1  (Fault)
Step 2: 1 3 -1  (Fault)
Step 3: 1 3 4  (Fault)
Step 4: 5 3 4  (Fault)
Step 5: 5 7 4  (Fault)
Step 6: 5 7 2  (Fault)
Step 7: 3 7 2  (Fault)
Step 8: 3 4 2  (Fault)
Step 9: 3 4 5  (Fault)
Step 10: 3 4 5 
FIFO Faults: 9

LRU:
Step 1: 1 -1 -1  (Fault)
Step 2: 1 3 -1  (Fault)
Step 3: 1 3 4  (Fault)
Step 4: 5 3 4  (Fault)
Step 5: 5 7 4  (Fault)
Step 6: 5 7 2  (Fault)
Step 7: 3 7 2  (Fault)
Step 8: 3 4 2  (Fault)
Step 9: 3 4 5  (Fault)
Step 10: 3 4 5 
LRU Faults: 9

Optimal:
Step 1: 1 -1 -1  (Fault)
Step 2: 1 3 -1  (Fault)
Step 3: 1 3 4  (Fault)
Step 4: 5 3 4  (Fault)
Step 5: 7 3 4  (Fault)
Step 6: 2 3 4  (Fault)
Step 7: 2 3 4 
Step 8: 2 3 4 
Step 9: 5 3 4  (Fault)
Step 10: 5 3 4 
Optimal Faults: 7


=== Code Execution Successful ===
