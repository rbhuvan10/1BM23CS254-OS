#include <stdio.h>

#define TIME_QUANTUM 3 // Time slice for Round Robin
#define MAX_PROCESSES 10

typedef struct {
int id, arrival, burst, remaining, waiting, turnaround;
} Process;

// Function to implement Round Robin Scheduling
void roundRobin(Process q[], int n, int tq) {
int time = 0, done = 0;
while (done < n) {
for (int i = 0; i < n; i++) {
if (q[i].remaining > 0) {
if (q[i].remaining > tq) {
time += tq;
q[i].remaining -= tq;
} else {
time += q[i].remaining;
q[i].waiting = time - q[i].arrival - q[i].burst;
q[i].turnaround = q[i].waiting + q[i].burst;
q[i].remaining = 0;
done++;
}
}
}
}
}

// Function to implement FCFS Scheduling
void fcfs(Process q[], int n) {
int time = 0;
for (int i = 0; i < n; i++) {
if (time < q[i].arrival)
time = q[i].arrival;
q[i].waiting = time - q[i].arrival;
q[i].turnaround = q[i].waiting + q[i].burst;
time += q[i].burst;
}
}

// Function to print process details
void printProcesses(Process q[], int n) {
printf("\nID\tArrival\tBurst\tWaiting\tTurnaround\n");
for (int i = 0; i < n; i++)
printf("%d\t%d\t%d\t%d\t%d\n", q[i].id, q[i].arrival, q[i].burst, q[i].waiting, q[i].turnaround);
}

int main() {
int n1, n2;
printf("Enter number of Round Robin processes: ");
scanf("%d", &n1);
Process q1[n1];

printf("Enter processes (ID Arrival Burst) for Round Robin:\n");
for (int i = 0; i < n1; i++) {
scanf("%d %d %d", &q1[i].id, &q1[i].arrival, &q1[i].burst);
q1[i].remaining = q1[i].burst;
}

printf("Enter number of FCFS processes: ");
scanf("%d", &n2);
Process q2[n2];

printf("Enter processes (ID Arrival Burst) for FCFS:\n");
for (int i = 0; i < n2; i++) {
scanf("%d %d %d", &q2[i].id, &q2[i].arrival, &q2[i].burst);
q2[i].remaining = q2[i].burst;
}

// Process scheduling
roundRobin(q1, n1, TIME_QUANTUM);
fcfs(q2, n2);

// Print results
printf("\n--- Round Robin Queue ---\n");
printProcesses(q1, n1);

printf("\n--- FCFS Queue ---\n");
printProcesses(q2, n2);

return 0;
}
