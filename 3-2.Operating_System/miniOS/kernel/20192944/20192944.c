#include "20192944.h"

int fork_exec()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "[*] Fork failed..\n");
    }

    if (pid == 0)
    {
        printf("[*] This is child process\n");
        printf("[*] Exit in 5 seconds..\n");
        sleep(5);
    }
    else
    {
        printf("[*] This is parent process..\n");
        wait(NULL);
        printf("[*] Exit in 5 seconds..\n");
        sleep(5);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

int ipc_prac()
{
    int pipefd[2];
    pid_t pid;
    char buffer[100];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        printf("[*] Child process..\n");
        close(pipefd[0]);

        printf("[*] INPUT: ");
        fgets(buffer, sizeof(buffer), stdin);
        write(pipefd[1], buffer, sizeof(buffer));

        close(pipefd[1]);
        printf("[*] End of child process...\n");
    }
    else
    {
        printf("[*] Parent process..\n");

        close(pipefd[1]);

        read(pipefd[0], buffer, sizeof(buffer));
        close(pipefd[0]);

        for (int i = 0; buffer[i]; i++)
        {
            buffer[i] = toupper(buffer[i]);
        }

        printf("\n[*] Returned string from child process: %s\n", buffer);
        printf("[*] End of parent process...\n");
    }

    return 0;
}

void *monte_carlo_with_mutex(void *arg)
{
    srand(time(NULL));
    int points_to_generate = TOTAL_POINTS / NUM_THREADS;
    int i;
    for (i = 0; i < points_to_generate; i++)
    {
        double x = (double)rand() / (double)RAND_MAX;
        double y = (double)rand() / (double)RAND_MAX;
        if (sqrt(x * x + y * y) <= 1.0)
        {
            pthread_mutex_lock(&mutex);
            points_in_circle++;
            pthread_mutex_unlock(&mutex);
        }
    }
    pthread_exit(NULL);
}

int estimate_pi_with_mutex()
{
    pthread_t threads[NUM_THREADS];
    int t;
    for (t = 0; t < NUM_THREADS; t++)
    {
        pthread_create(&threads[t], NULL, monte_carlo_with_mutex, NULL);
    }

    for (t = 0; t < NUM_THREADS; t++)
    {
        pthread_join(threads[t], NULL);
    }

    double pi_estimate = 4.0 * points_in_circle / (double)TOTAL_POINTS;
    printf("[*] Estimated pi: %f\n", pi_estimate);

    points_in_circle = 0;
    return 0;
}

void *monte_carlo_with_semaphore(void *arg)
{
    int points_to_generate = TOTAL_POINTS / NUM_THREADS;
    int i;
    for (i = 0; i < points_to_generate; i++)
    {
        double x = (double)rand() / (double)RAND_MAX;
        double y = (double)rand() / (double)RAND_MAX;
        if (sqrt(x * x + y * y) <= 1.0)
        {
            // Sync with sem
            sem_wait(&semaphore);
            points_in_circle++;
            sem_post(&semaphore);
        }
    }
    pthread_exit(NULL);
}

int estimate_pi_with_semaphore()
{
    pthread_t threads[NUM_THREADS];
    int t;

    // Initialize semaphore
    sem_init(&semaphore, 0, 1);

    // Seperate threads
    for (t = 0; t < NUM_THREADS; t++)
    {
        pthread_create(&threads[t], NULL, monte_carlo_with_semaphore, NULL);
    }

    for (t = 0; t < NUM_THREADS; t++)
    {
        pthread_join(threads[t], NULL);
    }

    double pi_estimate = 4.0 * points_in_circle / (double)TOTAL_POINTS;
    printf("[*] Estimated pi: %f\n", pi_estimate);

    // Destroy semaphore
    sem_destroy(&semaphore);
    points_in_circle = 0;
    return 0;
}

void round_robin()
{
    struct Process processes[MAX_PROCESSES];
    int num_processes;
    int time_quantum;

    printf("[*] Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("[*] Enter the time quantum: ");
    scanf("%d", &time_quantum);

    printf("[*] Enter burst times for each process:\n");
    for (int i = 0; i < num_processes; i++)
    {
        printf("[*] Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    int completed_processes = 0;
    int current_process = 0;

    while (completed_processes < num_processes)
    {
        if (processes[current_process].remaining_time > 0)
        {
            printf("[*] Running Process %d\n", processes[current_process].id);
            if (processes[current_process].remaining_time <= time_quantum)
            {
                printf("[*] Process %d completed\n", processes[current_process].id);
                completed_processes++;
                processes[current_process].remaining_time = 0;
            }
            else
            {
                processes[current_process].remaining_time -= time_quantum;
            }
        }
        current_process = (current_process + 1) % num_processes;
    }
    return;
}