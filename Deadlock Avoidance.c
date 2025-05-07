#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

int available[R] = {3, 3, 2};
int max[P][R] = {
{7, 5, 3},
{3, 2, 2},
{9, 0, 2},
{2, 2, 2},
{4, 3, 3}
};
int allocation[P][R] = {
{0, 1, 0},
{2, 0, 0},
{3, 0, 2},
{2, 1, 1},
{0, 0, 2}
};
int need[P][R];

void calculateNeed() {
for (int i = 0; i < P; i++)
for (int j = 0; j < R; j++)
need[i][j] = max[i][j] - allocation[i][j];
}

bool isSafe() {
int work[R];
bool finish[P] = {false};
for (int i = 0; i < R; i++)
work[i] = available[i];

int count = 0;
while (count < P) {
bool found = false;
for (int i = 0; i < P; i++) {
if (!finish[i]) {
int j;
for (j = 0; j < R; j++)
if (need[i][j] > work[j])
break;

if (j == R) {
for (int k = 0; k < R; k++)
work[k] += allocation[i][k];
finish[i] = true;
found = true;
count++;
}
}
}
if (!found) return false;
}
return true;
}

int main() {
calculateNeed();
if (isSafe())
printf("System is in a safe state.\n");
else
printf("System is NOT in a safe state.\n");
return 0;
}

Output:
System is in safe state.
