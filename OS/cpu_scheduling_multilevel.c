#include <stdio.h>

int main()
{
    int Q1_count, Q2_count, Q1_priority, Q2_priority, time = 0, wait_time = 0, turnaround_time = 0;
    printf("Enter the number of process in Q1: ");
    scanf("%d", &Q1_count);
    printf("Enter the number of process in Q2: ");
    scanf("%d", &Q2_count);
    int bt[Q1_count + Q2_count];
    printf("Enter the priority for Q1 and Q2 respectively: ");
    scanf("%d %d", &Q1_priority, &Q2_priority);
    int queue_count = Q1_priority > Q2_priority ? Q1_count : Q2_count;
    int queue = Q1_priority > Q2_priority ? 1 : 2;

    for (int i = 0; i < queue_count; i++)
    {
        printf("Enter the Burst Time for Q%d process %d: ", queue, i + 1);
        scanf("%d", &bt[i]);
    }
    for (int i = queue_count; i < Q1_count + Q2_count; i++)
    {
        printf("Enter the Burst Time for Q%d process %d: ", 3 - queue, i - queue_count + 1);
        scanf("%d", &bt[i]);
    }
    printf("\n\nProcess\t|Turnaround Time|Waiting Time\n");
    for (int i = 0; i < Q1_count + Q2_count; i++)
    {
        time += bt[i];
        wait_time += time - bt[i];
        turnaround_time += time;
        if (i < queue_count)
            printf("P[%d]\t|\t%d\t|\t%d\n", i + 1, time, time - bt[i]);
        else
            printf("P[%d]\t|\t%d\t|\t%d\n", i - queue_count + 1, time, time - bt[i]);
        if (i == queue_count - 1)
        {
            printf("\nAverage Waiting Time for Q%d = %0.2f\n", queue, (float)wait_time / queue_count);
            printf("Average Turnaround Time for Q%d = %0.2f\n", queue, (float)turnaround_time / queue_count);
            printf("\n\nProcess\t|Turnaround Time|Waiting Time\n");
        }
        else if (i == Q1_count + Q2_count - 1)
        {
            printf("\nAverage Waiting Time for Q%d = %0.2f\n", 3 - queue, (float)wait_time / (Q1_count + Q2_count - queue_count));
            printf("Average Turnaround Time for Q%d = %0.2f\n", 3 - queue, (float)turnaround_time / (Q1_count + Q2_count - queue_count));
        }
    }
}
