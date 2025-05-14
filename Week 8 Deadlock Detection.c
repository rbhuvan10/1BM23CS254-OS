#include <stdio.h>
#include <stdbool.h>

#define P 4
#define R 3

int allocation[P][R] = {
{0, 1, 0},
{2, 0, 0},
{3, 0, 3},
{2, 1, 1}
};

int request[P][R] = {
{0, 0, 0},
{2, 0, 2},
{0, 0, 0},
{1, 0, 0}
};

int available[R] = {0, 0, 0};

bool deadlockDetection() {
bool finish[P] = {false};
int work[R];
for (int i = 0; i < R; i++)
work[i] = available[i];

while (true) {
bool found = false;
for (int i = 0; i < P; i++) {
if (!finish[i]) {
bool canProceed = true;
for (int j = 0; j < R; j++) {
if (request[i][j] > work[j]) {
canProceed = false;
break;
}
}
if (canProceed) {
for (int j = 0; j < R; j++)
work[j] += allocation[i][j];
finish[i] = true;
found = true;
}
}
}
if (!found) break;
}

for (int i = 0; i < P; i++) {
if (!finish[i]) {
printf("Deadlock detected: Process %d is in deadlock.\n", i);
return true;
}
}
printf("No deadlock detected.\n");
return false;
}

int main() {
deadlockDetection();
return 0;
}

Output:
No deadlock detected
