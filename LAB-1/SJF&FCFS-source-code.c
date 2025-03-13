#include <stdio.h>
#include <limits.h>

void calculateFCFS(int at[], int bt[], int n, int ct[], int tat[], int wt[], int rt[]) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < at[i]) time = at[i];
        ct[i] = time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        rt[i] = time - at[i];
        time = ct[i];
    }
}

void calculateSJF(int at[], int bt[], int n, int ct[], int tat[], int wt[], int rt[]) {
    int time = 0, completed = 0, is_completed[n];
    for (int i = 0; i < n; i++) is_completed[i] = 0;
    
    while (completed < n) {
        int min_index = -1, min_bt = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !is_completed[i] && bt[i] < min_bt) {
                min_bt = bt[i];
                min_index = i;
            }
        }
        if (min_index == -1) time++;
        else {
            ct[min_index] = time + bt[min_index];
            tat[min_index] = ct[min_index] - at[min_index];
            wt[min_index] = tat[min_index] - bt[min_index];
            rt[min_index] = time - at[min_index];
            time = ct[min_index];
            is_completed[min_index] = 1;
            completed++;
        }
    }
}

void printResults(int at[], int bt[], int ct[], int tat[], int wt[], int rt[], int n) {
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int at[n], bt[n], ct[n], tat[n], wt[n], rt[n];
    
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
    }
    
    calculateFCFS(at, bt, n, ct, tat, wt, rt);
    printf("\nFirst Come First Serve (FCFS) Scheduling:\n");
    printResults(at, bt, ct, tat, wt, rt, n);
    
    calculateSJF(at, bt, n, ct, tat, wt, rt);
    printf("\nShortest Job First (SJF) Scheduling:\n");
    printResults(at, bt, ct, tat, wt, rt, n);
    
    return 0;
}
