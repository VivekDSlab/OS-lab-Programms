#include <stdio.h>444
struct Process {
    int id;
    int arrival;
    int burst;
    int waiting;
    int turnaround;
    int completion;
    int response;
};
void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}
void sortProcesses(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival > proc[j + 1].arrival) {
                swap(&proc[j], &proc[j + 1]);
            }
        }
    }
}
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process proc[n];
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Process %d: ", proc[i].id);
        scanf("%d %d", &proc[i].arrival, &proc[i].burst);
    }
    sortProcesses(proc, n);
    int currentTime = 0;
    float totalWaiting = 0, totalTurnaround = 0;
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\tResponse\n");
    for (int i = 0; i < n; i++) {
        if (currentTime < proc[i].arrival)
            currentTime = proc[i].arrival;  
        proc[i].completion = currentTime + proc[i].burst;
        proc[i].turnaround = proc[i].completion - proc[i].arrival;
        proc[i].waiting = proc[i].turnaround - proc[i].burst;
        proc[i].response = proc[i].waiting;
        totalWaiting += proc[i].waiting;
        totalTurnaround += proc[i].turnaround;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].id, proc[i].arrival, proc[i].burst,
               proc[i].waiting, proc[i].turnaround, proc[i].response);

        currentTime = proc[i].completion;
    }
    printf("\nAverage Waiting Time: %.2f", totalWaiting / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaround / n);
    return 0;
}
