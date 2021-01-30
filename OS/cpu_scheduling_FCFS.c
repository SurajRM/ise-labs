#include <stdio.h>

void main() {
    int proc_count, tmp = 0, total_time = 0, total_waiting_time = 0;
    printf("Enter the number of process: ");
    scanf("%d", &proc_count);
    int bt[proc_count], tt[proc_count];
    printf("Enter the Burst time for each process\n");
    for (int i = 0; i < proc_count; i++) {
        printf("\tP%d: ", i + 1);
        scanf("%d", &bt[i]);
        tmp += bt[i];
        total_time += tmp;
        if (i == proc_count - 1)
            continue;
        total_waiting_time += tmp;
    }
    printf("The average waiting time is: %0.3f\n", (float) total_waiting_time / proc_count);
    printf("The average turnaround time is %0.3f\n", (float) total_time / proc_count);
}