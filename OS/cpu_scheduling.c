#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ProcessTable {
    int process_count;
    int *burst_time;
} ProcessTable;

void fcfs(ProcessTable *);
void sjf(ProcessTable *);
void priority(ProcessTable *);
void round_robin(ProcessTable *);

int main() {
    ProcessTable *PT = (struct ProcessTable *) malloc(sizeof(ProcessTable));
    printf("\t\tCPU scheduling\n");
    printf("Enter the number of process: ");
    scanf("%d", &PT->process_count);

    PT->burst_time = (int *) malloc(PT->process_count * sizeof(int));
    printf("Enter the Burst time for each process\n");
    for (int i = 0; i < PT->process_count; i++) {
        printf("\tP%d: ", i + 1);
        scanf("%d", &PT->burst_time[i]);
    }

    fcfs(PT);
    sjf(PT);
    priority(PT);
    round_robin(PT);
    return 0;
}

void fcfs(ProcessTable *PT) {
    printf("\nFirst come first serve\n");
    int total_time = 0, total_waiting_time = 0, temp = 0;

    for (int i = 0; i < PT->process_count; i++) {
        temp += PT->burst_time[i];
        total_time += temp;
        if (i != PT->process_count - 1)
            total_waiting_time += temp;
    }

    printf("\tThe average waiting time is: %0.2f\n", (float) total_waiting_time / (float) PT->process_count);
    printf("\tThe average turnaround time is %0.2f\n", (float) total_time / (float) PT->process_count);
}

void sjf(ProcessTable *PT) {
    printf("\nShortest job first\n");
    int burst_time[PT->process_count], wait_time[PT->process_count + 1];
    int total_time = 0, total_waiting_time = 0;

    for (int i = 0; i < PT->process_count; i++) {
        burst_time[i] = PT->burst_time[i];
    }

    for (int i = 0; i < PT->process_count; i++) {
        for (int j = 0; j < PT->process_count - i - 1; j++) {
            if (burst_time[j] > burst_time[j + 1]) {
                burst_time[j] += burst_time[j + 1];
                burst_time[j + 1] = burst_time[j] - burst_time[j + 1];
                burst_time[j] = burst_time[j] - burst_time[j + 1];
            }
        }
    }

    wait_time[0] = 0;
    for (int i = 1; i <= PT->process_count; i++)
        wait_time[i] = wait_time[i - 1] + burst_time[i - 1];

    for (int i = 0; i < PT->process_count; i++) {
        total_time += wait_time[i];
        total_waiting_time += wait_time[i] + burst_time[i];
    }
    printf("\tThe average waiting time is %0.2f\n", (float) total_time / (float) PT->process_count);
    printf("\tThe average turnaround time is %0.2f\n", (float) total_waiting_time / (float) PT->process_count);
}

void priority(ProcessTable *PT) {
    printf("\nPriority scheduling\n");
    int burst_time[PT->process_count], priority[PT->process_count];
    int time = 0, wait_time = 0, turnaround_time = 0;

    printf("\tEnter Priority for each process\n");
    for (int i = 0; i < PT->process_count; i++) {
        printf("\t\tP%d: ", i + 1);
        scanf("%d", &priority[i]);
    }

    for (int i = 0; i < PT->process_count; i++) {
        burst_time[i] = PT->burst_time[i];
    }

    for (int i = 0; i < PT->process_count; i++) {
        for (int j = 0; j < PT->process_count - i - 1; j++) {
            if (priority[j] > priority[j + 1]) {
                priority[j] += priority[j + 1];
                priority[j + 1] = priority[j] - priority[j + 1];
                priority[j] = priority[j] - priority[j + 1];

                burst_time[j] += burst_time[j + 1];
                burst_time[j + 1] = burst_time[j] - burst_time[j + 1];
                burst_time[j] = burst_time[j] - burst_time[j + 1];
            }
        }
    }

    for (int i = 0; i < PT->process_count; i++) {
        time += burst_time[i];
        wait_time += time - burst_time[i];
        turnaround_time += time;
    }
    printf("\tAverage Waiting Time = %0.2f\n", (float) wait_time / (float) PT->process_count);
    printf("\tAverage Turnaround Time = %0.2f\n", (float) turnaround_time / (float) PT->process_count);
}

void round_robin(ProcessTable *PT) {
    printf("\nRound robin\n");
    int time_quantum, wait_time = 0, turnaround_time = 0, remaining = PT->process_count;
    int remaining_time[PT->process_count];
    bool flag;

    for (int i = 0; i < PT->process_count; i++) {
        remaining_time[i] = PT->burst_time[i];
    }

    printf("\tEnter time quantum: ");
    scanf("%d", &time_quantum);

    for (int time = 0, i = 0; remaining != 0; i = (i + 1) % PT->process_count) {
        if (remaining_time[i] <= time_quantum && remaining_time[i] > 0) {
            time += remaining_time[i];
            remaining_time[i] = 0;
            flag = true;
        } else if (remaining_time[i] > 0) {
            remaining_time[i] -= time_quantum;
            time += time_quantum;
        }
        if (remaining_time[i] == 0 && flag) {
            remaining--;
            wait_time += time - PT->burst_time[i];
            turnaround_time += time;
            flag = false;
        }
    }
    printf("\tAverage Waiting Time = %0.2f\n", (float) wait_time / (float) PT->process_count);
    printf("\tAverage Turnaround Time = %0.2f\n", (float) turnaround_time / (float) PT->process_count);
}

