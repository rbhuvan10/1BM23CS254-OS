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
    for (int i = 0; i < n;   i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].bt, proc[i].wt, proc[i].tat);
    }
}

void prioritySchedulingNonPreemptive(struct Process proc[], int n) {
    int total_wt = 0, total_tat = 0;

    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (proc[i].priority > proc[j].priority) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    proc[0].wt = 0;
    for (int i = 1; i < n; i++) {
        proc[i].wt = proc[i-1].wt + proc[i-1].bt;
        total_wt += proc[i].wt;
    }

    calculateWTAndTAT(proc, n);

    printf("\nNon-Preemptive Priority Scheduling:\n");
    displayResults(proc, n);
    printf("Average Waiting Time: %.2f\n", total_wt / (float)n);
    printf("Average Turnaround Time: %.2f\n", total_tat / (float)n);
}

void prioritySchedulingPreemptive(struct Process proc[], int n) {
    int total_wt = 0, total_tat = 0;
    int time = 0;

    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (proc[i].priority > proc[j].priority) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_bt > 0) {
                done = 0;
                time++;
                proc[i].remaining_bt--;

                if (proc[i].remaining_bt == 0) {
                    proc[i].tat = time;
                    proc[i].wt = proc[i].tat - proc[i].bt;
                    total_wt += proc[i].wt;
                    total_tat += proc[i].tat;
                }
            }
        }
        if (done == 1) break;
    }

    printf("\nPreemptive Priority Scheduling:\n");
    displayResults(proc, n);
    printf("Average Waiting Time: %.2f\n", total_wt / (float)n);
    printf("Average Turnaround Time: %.2f\n", total_tat / (float)n);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter Burst Time and Priority for Process %d: ", i + 1);
        scanf("%d %d", &proc[i].bt, &proc[i].priority);
        proc[i].remaining_bt = proc[i].bt;
    }

    prioritySchedulingNonPreemptive(proc, n);
    prioritySchedulingPreemptive(proc, n);

    return 0;
}

Output:
Enter number of processes: 3
Enter Burst Time and Priority for Process 1: 1 3
Enter Burst Time and Priority for Process 2: 2 5
Enter Burst Time and Priority for Process 3: 6 7

Non-Preemptive Priority Scheduling:
PID     Burst Time      Waiting Time    Turnaround Time
1       1               0               1
2       2               1               3
3       6               3               9
Average Waiting Time: 1.33
Average Turnaround Time: 4.33

Preemptive Priority Scheduling:
PID     Burst Time      Waiting Time    Turnaround Time
1       1               0               1
2       2               2               4
3       6               3               9
Average Waiting Time: 1.67
Average Turnaround Time: 4.67

Process returned 0 (0x0)   execution time : 17.335 s
Press any key to continue.
