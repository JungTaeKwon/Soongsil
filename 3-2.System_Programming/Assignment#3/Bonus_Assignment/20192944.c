#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 256
#define PROCESS_COUNT 4

int main(int argc, char *argv[])
{
    pid_t pids[5];
    int pipefd[5][2];
    pids[0] = getpid();
    int pipeNum;
    for (int i = 0; i < 5; i++)
    {
        if (pipe(pipefd[i]) == -1)
        {
            perror("[*] pipe creation error");
            exit(1);
        }
    }

    for (int i = 0; i < PROCESS_COUNT; i++)
    {
        if (pids[0] == getpid())
        {
            // printf("Fork in %d process\n", getpid());
            pids[i + 1] = fork();
            if (pids[i + 1] == 0)
            {
                pids[i + 1] = getpid();
            }
        }
    }

    for (int i = 0; i < PROCESS_COUNT + 1; i++)
    {
        if (pids[i] == getpid())
        {
            pipeNum = i;
        }
    }

    char tmpBuff[BUFFER_SIZE];

    if (getpid() == pids[0])
    {
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            perror("[*] fopen error");
            exit(1);
        }

        fgets(tmpBuff, BUFFER_SIZE, fp);
        printf("%d %s\n", getpid(), tmpBuff);

        // printf("Next pipe: %d\n", pipeNum + 1);
        write(pipefd[pipeNum + 1][1], "start", 5);
        fclose(fp);
    }
    int cnt = 5;
    while (cnt--)
    {
        // printf("pid: %d, pipeNum: %d\n", getpid(), pipeNum);

        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            perror("[*] fopen error");
            exit(1);
        }
        // printf("waiting from %d\n", pipeNum);
        read(pipefd[pipeNum][0], tmpBuff, sizeof(tmpBuff));
        // printf("%d received %s\n", getpid(), tmpBuff);

        fgets(tmpBuff, BUFFER_SIZE, fp);
        printf("%d %s\n", getpid(), tmpBuff);

        // printf("Next pipe: %d\n", pipeNum + 1);
        write(pipefd[pipeNum + 1][1], "next", 4);
        fclose(fp);
    }

    for (int i = PROCESS_COUNT; i >= 0; i--)
    {
        int status;
        pid_t pid = waitpid(pids[i], &status, 0);
        printf("%d I'm exiting...\n", pid);
    }
    printf("%d I'm exiting..\n", getpid());
    return 0;
}