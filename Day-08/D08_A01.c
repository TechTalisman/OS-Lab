#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

void print_gantt_chart(int timeline[], int timeline_length,
                       int completion_times[])
{
    if (timeline_length == 0)
    {
        printf("\nNo process execution recorded.\n");
        return;
    }

    printf("\nDetailed Gantt Chart Representation:\n");

    for (int i = 0; i < timeline_length; i++)
    {
        if (timeline[i] == -1)
            printf("  Idle  ");
        else
            printf("  P%d  ", timeline[i]);
    }

    printf("\n");

    printf("Timeline:\n");
    printf("0");

    for (int i = 0; i < timeline_length; i++)
    {
        printf("    %d", completion_times[i]);
    }

    printf("\n");

    // Simplified Gantt Chart
    printf("\nSimplified Gantt Chart:\n");

    printf("0");

    int current_process = timeline[0];

    for (int i = 1; i < timeline_length; i++)
    {
        if (timeline[i] != current_process)
        {
            if (current_process == -1)
                printf(" | Idle | %d", completion_times[i - 1]);
            else
                printf(" | P%d | %d", current_process, completion_times[i - 1]);

            current_process = timeline[i];
        }
    }

    if (current_process == -1)
        printf(" | Idle | %d", completion_times[timeline_length - 1]);
    else
        printf(" | P%d | %d", current_process,
               completion_times[timeline_length - 1]);

    printf("\n");
}

void sjf_preemptive_scheduling(Process processes[], int n)
{
    int completed = 0;
    int time = 0;

    int timeline[1000];
    int completion_times[1000];
    int timeline_length = 0;

    // Initialize remaining time
    for (int i = 0; i < n; i++)
    {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
    }

    while (completed < n)
    {
        int min_index = -1;
        int min_remaining_time = INT_MAX;

        // Find process with shortest remaining time
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= time &&
                processes[i].remaining_time > 0)
            {
                if (processes[i].remaining_time < min_remaining_time)
                {
                    min_remaining_time = processes[i].remaining_time;
                    min_index = i;
                }
                else if (processes[i].remaining_time == min_remaining_time)
                {
                    // Tie-breaking: earlier arrival time
                    if (min_index == -1 ||
                        processes[i].arrival_time <
                        processes[min_index].arrival_time)
                    {
                        min_index = i;
                    }
                }
            }
        }

        // CPU is idle
        if (min_index == -1)
        {
            timeline[timeline_length] = -1;
            completion_times[timeline_length] = time + 1;
            timeline_length++;

            time++;
            continue;
        }

        // Execute selected process for one time unit
        processes[min_index].remaining_time--;

        timeline[timeline_length] =
            processes[min_index].process_id;

        completion_times[timeline_length] = time + 1;

        timeline_length++;

        time++;

        // Process completed
        if (processes[min_index].remaining_time == 0)
        {
            processes[min_index].completion_time = time;

            processes[min_index].turnaround_time =
                processes[min_index].completion_time -
                processes[min_index].arrival_time;

            processes[min_index].waiting_time =
                processes[min_index].turnaround_time -
                processes[min_index].burst_time;

            completed++;
        }
    }

    print_gantt_chart(timeline, timeline_length, completion_times);

    printf("\nProcess Details:\n");
    printf("-----------------------------------------------------------------\n");
    printf("| Process | Arrival | Burst | Completion | Waiting | Turnaround |\n");
    printf("-----------------------------------------------------------------\n");

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

    printf("-----------------------------------------------------------------\n");
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
    }

    fclose(data_file);
    fclose(properties_file);

    sjf_preemptive_scheduling(processes, n);

    return 0;
}
