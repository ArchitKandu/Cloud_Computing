#include <stdio.h>
void turnarroundtime(int processes[], int n, int bt[], int wt[], int tat[]) {
   for (int i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}
void waitingtime(int processes[], int n, int bt[], int wt[], int quantum) {
   int rem_bt[n];
   for (int i = 0 ; i < n ; i++)
   rem_bt[i] = bt[i];
   int t = 0;
   while (1) {
      int done = 0;
      for (int i = 0 ; i < n; i++) {
         if (rem_bt[i] > 0) {
            done = 1;
            if (rem_bt[i] > quantum) {
               t += quantum;
               rem_bt[i] -= quantum;
            }
            else {
               t = t + rem_bt[i];
               wt[i] = t - bt[i];
               rem_bt[i] = 0;
            }
         }
      }
      if (done == 0)
         break;
   }
}
void findavgTime(int processes[], int n, int bt[], int quantum) {
   int wt[n], tat[n], total_wt = 0, total_tat = 0;
   waitingtime(processes, n, bt, wt, quantum);
   turnarroundtime(processes, n, bt, wt, tat);
   printf("\nProcesses \tBurst Time \tWaiting Time \tTurnaround time\n");
   for (int i=0; i<n; i++) {
      total_wt = total_wt + wt[i];
      total_tat = total_tat + tat[i];
      printf("%d\t\t%d\t\t%d\t\t%d\n",i+1, bt[i], wt[i], tat[i]);
   }
   printf("\nAverage waiting time = %.2f\n", (float)total_wt / (float)n);
   printf("Average turnaround time = %.2f\n\n", (float)total_tat / (float)n);
}
int main() {
   int processes[] = { 1, 2, 3};
   int n = sizeof processes / sizeof processes[0];
   int burst_time[] = {8, 6, 12};
   int quantum = 2;
   findavgTime(processes, n, burst_time, quantum);
   return 0;
}
