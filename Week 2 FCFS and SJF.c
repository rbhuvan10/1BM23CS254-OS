#include <stdio.h>
#include <stdbool.h>

void sortByArrivalAndBurst(int n, int at[], int bt[], int index[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1] || (at[j] == at[j + 1] && bt[j] > bt[j + 1])) {
                int temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;
                temp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp;
            }
        }
    }
}

void fcfs(int n, int at[], int bt[], int ct[], int tat[], int wt[]) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < at[i]) time = at[i];
        ct[i] = time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        time = ct[i];
    }
}

void sjfNonPreemptive(int n, int at[], int bt[], int ct[], int tat[], int wt[]) {
    int remaining[n], completed = 0, current_time = 0;
    for (int i = 0; i < n; i++) {
        remaining[i] = bt[i];
        ct[i] = -1;
    }
    while (completed < n) {
        int shortest = -1, shortest_bt = 999999;
        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && remaining[i] > 0 && remaining[i] < shortest_bt) {
                shortest = i;
                shortest_bt = remaining[i];
            }
        }
        if (shortest == -1) {
            current_time++;
            continue;
        }
        ct[shortest] = current_time + remaining[shortest];
        tat[shortest] = ct[shortest] - at[shortest];
        wt[shortest] = tat[shortest] - bt[shortest];
        remaining[shortest] = 0;
        completed++;
        current_time = ct[shortest];
    }
}

void sjfPreemptive(int n, int at[], int bt[], int ct[], int tat[], int wt[]) {
    int remaining[n], completed = 0, current_time = 0;
    for (int i = 0; i < n; i++) {
        remaining[i] = bt[i];
        ct[i] = -1;
    }
    while (completed < n) {
        int shortest = -1, shortest_bt = 999999;
        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && remaining[i] > 0 && remaining[i] < shortest_bt) {
                shortest = i;
                shortest_bt = remaining[i];
            }
        }
        if (shortest == -1) {
            current_time++;
            continue;
        }
        remaining[shortest]--;
        current_time++;
        if (remaining[shortest] == 0) {
            ct[shortest] = current_time;
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
            completed++;
        }
    }
}

void displayResults(int n, int at[], int bt[], int ct[], int tat[], int wt[]) {
    int totalTAT = 0, totalWT = 0;
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
        totalTAT += tat[i];
        totalWT += wt[i];
    }
    float avgTAT = (float)totalTAT / n;
    float avgWT = (float)totalWT / n;
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT);
    printf("Average Waiting Time: %.2f\n", avgWT);
}

int main() {
    int n;
    int at[100], bt[100], ct[100], tat[100], wt[100];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Arrival Time and Burst Time:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    for (int i = 0; i < n; i++) ct[i] = tat[i] = wt[i] = 0;
    printf("\nFCFS Scheduling\n");
    fcfs(n, at, bt, ct, tat, wt);
    displayResults(n, at, bt, ct, tat, wt);

    for (int i = 0; i < n; i++) ct[i] = tat[i] = wt[i] = 0;
    printf("\nSJF Non-Preemptive Scheduling\n");
    sjfNonPreemptive(n, at, bt, ct, tat, wt);
    displayResults(n, at, bt, ct, tat, wt);

    for (int i = 0; i < n; i++) ct[i] = tat[i] = wt[i] = 0;
    printf("\nSJF Preemptive (SRTF) Scheduling\n");
    sjfPreemptive(n, at, bt, ct, tat, wt);
    displayResults(n, at, bt, ct, tat, wt);

    return 0;
}

Output:
Enter number of processes: 3
Enter Arrival Time and Burst Time:
Process 1: 1 5 
Process 2: 3 4 
Process 3: 0 2

FCFS Scheduling

Process	Arrival	Burst	Completion	Turnaround	Waiting
1	1	5	6		5		0
2	3	4	10		7		3
3	0	2	12		12		10

Average Turnaround Time: 8.00
Average Waiting Time: 4.33

SJF Non-Preemptive Scheduling

Process	Arrival	Burst	Completion	Turnaround	Waiting
1	1	5	7		6		1
2	3	4	11		8		4
3	0	2	2		2		0

Average Turnaround Time: 5.33
Average Waiting Time: 1.67

SJF Preemptive (SRTF) Scheduling

Process	Arrival	Burst	Completion	Turnaround	Waiting
1	1	5	7		6		1
2	3	4	11		8		4
3	0	2	2		2		0

Average Turnaround Time: 5.33
Average Waiting Time: 1.67
