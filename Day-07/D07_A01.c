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

    // Gantt Chart Representation
    printf("\nGantt Chart Representation:\n");

    int time = 0;

    for (int i = 0; i < n; i++)
    {
        // Show CPU idle time if necessary
        if (time < processes[i].arrival_time)
        {
            printf("| Idle ");
            time = processes[i].arrival_time;
        }

        printf("| P%d ", processes[i].process_id);
        time = processes[i].completion_time;
    }

    printf("|\n");

    // Timeline
    printf("0");

    time = 0;

    for (int i = 0; i < n; i++)
    {
        if (time < processes[i].arrival_time)
        {
            printf("    %d", processes[i].arrival_time);
            time = processes[i].arrival_time;
        }

        printf("    %d", processes[i].completion_time);
        time = processes[i].completion_time;
    }

    printf("\n");
}

void fcfs_scheduling(Process processes[], int n)
{
    int completion_time = 0;

    // Sort processes according to arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (processes[i].arrival_time > processes[j].arrival_time)
            {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Calculate scheduling times
    for (int i = 0; i < n; i++)
    {
        // CPU remains idle until the process arrives
        if (completion_time < processes[i].arrival_time)
        {
            completion_time = processes[i].arrival_time;
        }

        processes[i].completion_time =
            completion_time + processes[i].burst_time;

        processes[i].turnaround_time =
            processes[i].completion_time - processes[i].arrival_time;

        processes[i].waiting_time =
            processes[i].turnaround_time - processes[i].burst_time;

        completion_time = processes[i].completion_time;
    }

    print_gantt_chart(processes, n, "FCFS");
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

    // Read number of processes
    if (fscanf(properties_file, "%d", &n) != 1 || n <= 0)
    {
        printf("Invalid number of processes.\n");
        fclose(data_file);
        fclose(properties_file);
        return 1;
    }

    Process processes[n];

    // Read process details
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
    }

    fclose(data_file);
    fclose(properties_file);

    // Perform FCFS scheduling
    fcfs_scheduling(processes, n);

    return 0;
}
