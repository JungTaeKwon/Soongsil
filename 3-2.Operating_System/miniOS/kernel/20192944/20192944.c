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
