#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int bt;
    int wt;
    int tat;
    int priority;
    int remaining_bt;
};

void calculateWTAndTAT(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].wt + proc[i].bt;
    }
}

void displayResults(struct Process proc[], int n) {
    printf("PID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].bt, proc[i].wt, proc[i].tat);
    }
}

void roundRobinScheduling(struct Process proc[], int n, int quantum) {
    int total_wt = 0, total_tat = 0;
    int remaining_proc = n;
    int time = 0;

    for (int i = 0; i < n; i++) {
        proc[i].remaining_bt = proc[i].bt;
    }

    while (remaining_proc > 0) {
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_bt > 0) {
                if (proc[i].remaining_bt > quantum) {
                    proc[i].remaining_bt -= quantum;
                    time += quantum;
                } else {
                    time += proc[i].remaining_bt;
                    proc[i].wt = time - proc[i].bt;
                    proc[i].tat = time;
                    proc[i].remaining_bt = 0;
                    total_wt += proc[i].wt;
                    total_tat += proc[i].tat;
                    remaining_proc--;
                }
            }
        }
    }

    displayResults(proc, n);
    printf("Average Waiting Time: %.2f\n", total_wt / (float)n);
    printf("Average Turnaround Time: %.2f\n", total_tat / (float)n);
}

void ct_roundRobinScheduling(struct Process proc[], int n, int quantum) {
    roundRobinScheduling(proc, n, quantum);
}

int main() {
    int n, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &proc[i].bt);
        proc[i].remaining_bt = proc[i].bt;
    }

    printf("Enter the quantum size for Round Robin: ");
    scanf("%d", &quantum);

    ct_roundRobinScheduling(proc, n, quantum);

    return 0;
}

Output:
Enter number of processes: 3
Enter Burst Time for Process 1: 2
Enter Burst Time for Process 2: 6
Enter Burst Time for Process 3: 5
Enter the quantum size for Round Robin: 3
PID     Burst Time      Waiting Time    Turnaround Time
1       2               0               2
2       6               5               11
3       5               8               13
Average Waiting Time: 4.33
Average Turnaround Time: 8.67

Process returned 0 (0x0)   execution time : 9.748 s
Press any key to continue.
