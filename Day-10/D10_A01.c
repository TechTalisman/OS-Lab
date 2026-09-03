#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100
#define MAX_QUEUE_SIZE 10000

typedef struct
{
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void read_process_data(Process processes[], int *n)
{
    FILE *file = fopen("process_data.txt", "r");

    if (file == NULL)
    {
        printf("Error: Cannot open process_data.txt\n");
        exit(1);
    }

    *n = 0;

    while (*n < MAX_PROCESSES &&
           fscanf(file, "%d %d %d",
                  &processes[*n].pid,
                  &processes[*n].arrival_time,
                  &processes[*n].burst_time) == 3)
    {
        if (processes[*n].arrival_time < 0 ||
            processes[*n].burst_time <= 0)
        {
            printf("Error: Invalid process data.\n");
            fclose(file);
            exit(1);
        }

        processes[*n].remaining_time = processes[*n].burst_time;
        (*n)++;
    }

    fclose(file);

    if (*n == 0)
    {
        printf("Error: No process data found.\n");
        exit(1);
    }
}

void add_arrived_processes(Process processes[], int n,
                           int time, int added[],
                           int queue[], int *rear)
{
    for (int i = 0; i < n; i++)
    {
        if (!added[i] &&
            processes[i].arrival_time <= time &&
            processes[i].remaining_time > 0)
        {
            queue[*rear] = i;
            (*rear)++;
            added[i] = 1;
        }
    }
}

void round_robin_scheduling(Process processes[], int n, int time_quantum)
{
    int queue[MAX_QUEUE_SIZE];
    int added[MAX_PROCESSES] = {0};

    int front = 0;
    int rear = 0;
    int time = 0;
    int completed = 0;

    int gantt_process[MAX_QUEUE_SIZE];
    int gantt_time[MAX_QUEUE_SIZE + 1];
    int gantt_size = 0;

    while (completed < n)
    {
        add_arrived_processes(processes, n, time,
                              added, queue, &rear);

        if (front == rear)
        {
            int next_arrival = -1;

            for (int i = 0; i < n; i++)
            {
                if (!added[i] && processes[i].remaining_time > 0)
                {
                    if (next_arrival == -1 ||
                        processes[i].arrival_time < next_arrival)
                    {
                        next_arrival = processes[i].arrival_time;
                    }
                }
            }

            if (next_arrival != -1)
            {
                time = next_arrival;
                add_arrived_processes(processes, n, time,
                                      added, queue, &rear);
            }
        }

        if (front == rear)
            continue;

        int index = queue[front++];

        gantt_process[gantt_size] = processes[index].pid;
        gantt_time[gantt_size] = time;
        gantt_size++;

        int execution_time = processes[index].remaining_time;

        if (execution_time > time_quantum)
            execution_time = time_quantum;

        time += execution_time;
        processes[index].remaining_time -= execution_time;

        /* Add processes that arrived during execution */
        add_arrived_processes(processes, n, time,
                              added, queue, &rear);

        if (processes[index].remaining_time > 0)
        {
            queue[rear++] = index;
        }
        else
        {
            processes[index].completion_time = time;

            processes[index].turnaround_time =
                processes[index].completion_time -
                processes[index].arrival_time;

            processes[index].waiting_time =
                processes[index].turnaround_time -
                processes[index].burst_time;

            completed++;
        }
    }

    gantt_time[gantt_size] = time;

    printf("\nGantt Chart:\n");

    printf(" ");
    for (int i = 0; i < gantt_size; i++)
    {
        printf("-------");
    }
    printf("\n|");

    for (int i = 0; i < gantt_size; i++)
    {
        printf("  P%-3d|", gantt_process[i]);
    }

    printf("\n ");

    for (int i = 0; i < gantt_size; i++)
    {
        printf("-------");
    }

    printf("\n");

    printf("%d", gantt_time[0]);

    for (int i = 1; i <= gantt_size; i++)
    {
        printf("      %d", gantt_time[i]);
    }

    printf("\n");
}

void print_results(Process processes[], int n)
{
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
    }
}

int main()
{
    Process processes[MAX_PROCESSES];
    int n;
    int time_quantum;

    printf("Enter the time quantum: ");

    if (scanf("%d", &time_quantum) != 1 ||
        time_quantum <= 0)
    {
        printf("Error: Time quantum must be a positive integer.\n");
        return 1;
    }

    read_process_data(processes, &n);

    round_robin_scheduling(processes, n, time_quantum);

    print_results(processes, n);

    return 0;
}
