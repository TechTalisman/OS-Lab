#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

typedef struct
{
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

void read_process_data(Process processes[], int *n)
{
    FILE *file = fopen("process_data.txt", "r");

    if (!file)
    {
        printf("Error: Cannot open process_data.txt\n");
        exit(1);
    }

    *n = 0;

    while (*n < MAX_PROCESSES &&
           fscanf(file, "%d %d %d",
                  &processes[*n].id,
                  &processes[*n].arrival_time,
                  &processes[*n].burst_time) == 3)
    {
        if (processes[*n].arrival_time < 0 || processes[*n].burst_time <= 0)
        {
            printf("Error: Invalid process data.\n");
            fclose(file);
            exit(1);
        }

        (*n)++;
    }

    fclose(file);

    if (*n == 0)
    {
        printf("Error: No process data found.\n");
        exit(1);
    }
}

void calculate_hrrn(Process processes[], int n,
                    int gantt_chart[], int gantt_time[], int *gantt_size)
{
    int completed = 0;
    int current_time = 0;
    int is_completed[MAX_PROCESSES] = {0};

    *gantt_size = 0;

    while (completed < n)
    {
        int selected = -1;
        float highest_rr = -1.0;

        for (int i = 0; i < n; i++)
        {
            if (!is_completed[i] &&
                processes[i].arrival_time <= current_time)
            {
                int waiting_time =
                    current_time - processes[i].arrival_time;

                float response_ratio =
                    (waiting_time + processes[i].burst_time) /
                    (float)processes[i].burst_time;

                if (response_ratio > highest_rr)
                {
                    highest_rr = response_ratio;
                    selected = i;
                }
                else if (response_ratio == highest_rr &&
                         selected != -1 &&
                         processes[i].arrival_time <
                         processes[selected].arrival_time)
                {
                    selected = i;
                }
            }
        }

        if (selected == -1)
        {
            current_time++;
            continue;
        }

        Process *p = &processes[selected];

        gantt_chart[*gantt_size] = p->id;
        gantt_time[*gantt_size] = current_time;
        (*gantt_size)++;

        p->waiting_time = current_time - p->arrival_time;
        p->completion_time = current_time + p->burst_time;
        p->turnaround_time =
            p->completion_time - p->arrival_time;

        current_time = p->completion_time;

        is_completed[selected] = 1;
        completed++;
    }

    gantt_time[*gantt_size] = current_time;
}

void print_results(Process processes[], int n)
{
    printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
    }
}

void print_gantt_chart(int gantt_chart[],
                       int gantt_time[],
                       int gantt_size)
{
    printf("\nGantt Chart:\n");

    printf(" ");
    for (int i = 0; i < gantt_size; i++)
    {
        printf("-------");
    }
    printf("\n|");

    for (int i = 0; i < gantt_size; i++)
    {
        printf("  P%d  |", gantt_chart[i]);
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

int main()
{
    Process processes[MAX_PROCESSES];
    int n;

    int gantt_chart[MAX_PROCESSES];
    int gantt_time[MAX_PROCESSES + 1];
    int gantt_size;

    read_process_data(processes, &n);

    calculate_hrrn(processes, n,
                   gantt_chart,
                   gantt_time,
                   &gantt_size);

    print_results(processes, n);

    print_gantt_chart(gantt_chart,
                      gantt_time,
                      gantt_size);

    return 0;
}
