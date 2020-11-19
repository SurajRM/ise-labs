#include <stdio.h>
#include <stdlib.h>

#define sf scanf
#define pf printf

int p;
void fcfs(int q[], int initialwaittime, int np) {
    int turn[np], wait[np], turnsum = initialwaittime + q[0], waitsum = initialwaittime, i;
    turn[0] = q[0] + initialwaittime;
    wait[0] = initialwaittime;

    for (i = 1; i < np; i++) {
        wait[i] = wait[i - 1] + q[i - 1];
        turn[i] = wait[i] + q[i];
        turnsum += turn[i];
        waitsum += wait[i];
    }

    printf("\nProcess\t\tBurst time\t\tWaiting time\t\tTurnaround time\n");
    for (int i = 0; i < np; i++) {
        printf("P%d\t\t%d\t\t\t%d\t\t\t%d\n", p++, q[i], wait[i], turn[i]);
    }
    printf("\nAverage Waiting time: %.2f\nAverage Turn-around time: %.2f\n\n\n", (float)waitsum / np, (float)turnsum / np);
}

int main() {
    int p1, p2;
    pf("Enter priority for Queue 1: ");
    sf("%d", &p1);
    pf("Enter priority for Queue 2: ");
    sf("%d", &p2);
    int np1, np2, i, w1 = 0, w2 = 0;
    if (p1 == p2) {
        pf("Priority cannot be the same\n");
        exit(0);
    }

    pf("Enter the number of process of Queue 1: ");
    sf("%d", &np1);
    int q1[np1];
    for (i = 0; i < np1; i++) {
        pf("Enter the burst time for Process %d: ", i + 1);
        sf("%d", &q1[i]);
        w1 += q1[i];
    }

    pf("Enter the number of process of Queue 2: ");
    sf("%d", &np2);
    int q2[np2];
    for (i = 0; i < np2; i++) {
        pf("Enter the burst time for Process %d: ", i + np1 + 1);
        sf("%d", &q2[i]);
        w2 += q2[i];
    }
    
    if (p1 < p2) {
        pf("\nQUEUE 1:\n");
        p = 1;
        fcfs(q1, 0, np1);
        pf("\nQUEUE 2:\n");
        fcfs(q2, w1, np2);
    } else {
        pf("\nQUEUE 2:\n");
        p = np1 + 1;
        fcfs(q2, 0, np2);
        pf("\nQUEUE 1:\n");
        p = 1;
        fcfs(q1, w2, np1);
    }
    return 0;
}