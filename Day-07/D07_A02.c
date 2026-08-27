#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

void print_gantt_chart(Process processes[], int n, const char *algorithm)
{
    printf("\nGantt Chart (%s):\n", algorithm);
    printf("---------------------------------------------------------------\n");
    printf("| Process | Arrival | Burst | Completion | Waiting | Turnaround |\n");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("|   P%-4d |   %-5d | %-5d |    %-8d | %-7d | %-10d |\n",
               processes[i].process_id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].waiting_time,
               processes[i].turnaround_time);
    }

    printf("---------------------------------------------------------------\n");

    printf("\nGantt Chart Representation:\n");

    int time = 0;

    for (int i = 0; i < n; i++)
    {
        if (time < processes[i].arrival_time)
        {
            printf("| Idle ");
            time = processes[i].arrival_time;
        }

        printf("| P%d ", processes[i].process_id);
        time = processes[i].completion_time;
    }

    printf("|\n");

    printf("Timeline:\n");

    time = 0;
    printf("%d", time);

    for (int i = 0; i < n; i++)
    {
        if (time < processes[i].arrival_time)
        {
            time = processes[i].arrival_time;
            printf("     %d", time);
        }

        time = processes[i].completion_time;
        printf("     %d", time);
    }

    printf("\n");
}

void sjf_non_preemptive_scheduling(Process processes[], int n)
{
    int completed = 0;
    int current_time = 0;

    while (completed < n)
    {
        int shortest = -1;

        // Find the shortest job among arrived processes
        for (int i = 0; i < n; i++)
        {
            if (processes[i].completion_time == 0 &&
                processes[i].arrival_time <= current_time)
            {
                if (shortest == -1 ||
                    processes[i].burst_time < processes[shortest].burst_time)
                {
                    shortest = i;
                }
            }
        }

        // If no process has arrived, move time forward
        if (shortest == -1)
        {
            current_time++;

            continue;
        }

        // Execute selected process
        processes[shortest].completion_time =
            current_time + processes[shortest].burst_time;

        processes[shortest].turnaround_time =
            processes[shortest].completion_time -
            processes[shortest].arrival_time;

        processes[shortest].waiting_time =
            processes[shortest].turnaround_time -
            processes[shortest].burst_time;

        current_time = processes[shortest].completion_time;

        completed++;
    }

    /*
     * Reorder processes according to execution order
     * for displaying the Gantt chart.
     */
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (processes[i].completion_time >
                processes[j].completion_time)
            {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    print_gantt_chart(processes, n, "SJF Non-Preemptive");
}

int main()
{
    int n;

    FILE *data_file = fopen("process_data.txt", "r");
    FILE *properties_file = fopen("process_properties.txt", "r");

    if (data_file == NULL || properties_file == NULL)
    {
        printf("Error opening input files!\n");
        return 1;
    }

    if (fscanf(properties_file, "%d", &n) != 1 || n <= 0)
    {
        printf("Invalid number of processes.\n");

        fclose(data_file);
        fclose(properties_file);

        return 1;
    }

    Process processes[n];

    for (int i = 0; i < n; i++)
    {
        if (fscanf(data_file, "%d %d %d",
                   &processes[i].process_id,
                   &processes[i].arrival_time,
                   &processes[i].burst_time) != 3)
        {
            printf("Invalid process data.\n");

            fclose(data_file);
            fclose(properties_file);

            return 1;
        }

        // 0 means process has not completed yet
        processes[i].completion_time = 0;
    }

    fclose(data_file);
    fclose(properties_file);

    sjf_non_preemptive_scheduling(processes, n);

    return 0;
}
