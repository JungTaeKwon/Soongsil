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

void *monte_carlo(void *arg)
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

int estimate_pi()
{
    pthread_t threads[NUM_THREADS];
    int t;
    for (t = 0; t < NUM_THREADS; t++)
    {
        pthread_create(&threads[t], NULL, monte_carlo, NULL);
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
