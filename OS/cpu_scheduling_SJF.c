#include <stdio.h>

int main() {
    int n, bt[40], i, wt[40], sum = 0, temp, j, p[40], temp2, tt = 0;
    double avgwt;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter the Burst time for each process\n");
    for (i = 0; i < n; i++) {
        printf("\tP%d: ", i + 1);
        scanf("%d", &bt[i]);
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (bt[j] > bt[j + 1]) {
                temp = bt[j + 1];
                bt[j + 1] = bt[j];
                bt[j] = temp;
            }
        }
    }
    wt[0] = 0;
    for (i = 1; i <= n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }
    for (i = 0; i < n; i++) {
        sum = sum + wt[i];
        tt += wt[i] + bt[i];
    }
    printf("The average waiting time is %0.3f\n", (float) sum / n);
    printf("The average turnaround time is %0.3f\n", (float) tt / n);
    return 0;
}