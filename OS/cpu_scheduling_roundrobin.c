#include <stdio.h>

int main() {

    int count, remaining, flag = 0, time_quantum;
    int wait_time = 0, turnaround_time = 0;
    printf("Enter process count: ");
    scanf("%d", &count);
    int bt[count], rt[count];
    remaining = count;
    for (int i = 0; i < count; i++) {
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }
    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);
    printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");
    for (int time = 0, i = 0; remaining != 0; i = (i + 1) % count) {
        if (rt[i] <= time_quantum && rt[i] > 0) {
            time += rt[i];
            rt[i] = 0;
            flag = 1;
        } else if (rt[i] > 0) {
            rt[i] -= time_quantum;
            time += time_quantum;
        }
        if (rt[i] == 0 && flag == 1) {
            remaining--;
            printf("P[%d]\t|\t%d\t|\t%d\n", i + 1, time, time - bt[i]);
            wait_time += time - bt[i];
            turnaround_time += time;
            flag = 0;
        }
    }
    printf("\nAverage Waiting Time = %0.2f\n", (float) wait_time / count);
    printf("Average Turnaround Time = %0.2f\n", (float) turnaround_time / count);

    return 0;
}