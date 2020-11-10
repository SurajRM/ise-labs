
#include <stdio.h>

int main()
{
    int count, temp = 0, time = 0, wait_time = 0, turnaround_time = 0;
    printf("Enter total number of Process: ");
    scanf("%d", &count);
    int bt[count], p[count], pr[count];

    for (int i = 0; i < count; i++)
    {
        printf("Enter Burst Time and Priority for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        scanf("%d", &pr[i]);
        p[i] = i + 1;
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (pr[j] > pr[j + 1])
            {

                temp = pr[j + 1];
                pr[j + 1] = pr[j];
                pr[j] = temp;

                temp = bt[j + 1];
                bt[j + 1] = bt[j];
                bt[j] = temp;

                temp = p[j + 1];
                p[j + 1] = p[j];
                p[j] = temp;
            }
        }
    }

    printf("\n\nProcess\t| Priority\t| Turnaround Time\t| Waiting Time\n\n");
    for (int i = 0; i < count; i++)
    {
        time += bt[i];
        wait_time += time - bt[i];
        turnaround_time += time;
        printf("P[%d]\t| %d\t\t| %d\t\t\t| %d\n", p[i], pr[i], turnaround_time, wait_time);
    }

    printf("\nAverage Waiting Time = %0.2f\n", (float)wait_time / count);
    printf("Average Turnaround Time = %0.2f\n", (float)turnaround_time / count);

    return 0;
}