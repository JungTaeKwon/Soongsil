// #include <stdio.h>
#include "20192944.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 256
#define PROCESS_COUNT 4

int checkOffset(char *str);

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
        printf("%d %s", getpid(), tmpBuff);

        write(pipefd[pipeNum + 1][1], tmpBuff, sizeof(tmpBuff));
        fclose(fp);
    }

    while (1)
    {
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            perror("[*] fopen error");
            exit(1);
        }
        read(pipefd[pipeNum][0], tmpBuff, sizeof(tmpBuff));
        int offsetCnt = checkOffset(tmpBuff);
        if (offsetCnt == -1)
        {
            write(pipefd[pipeNum - 1][1], "\0", 1);
            break;
        }
        for (int i = 0; i < offsetCnt; i++)
        {
            fgets(tmpBuff, BUFFER_SIZE, fp);
        }
        fgets(tmpBuff, BUFFER_SIZE, fp);

        if (tmpBuff[strlen(tmpBuff) - 1] != '\n')
        {
            printf("%d %s\n", getpid(), tmpBuff);
        }
        else
        {
            printf("%d %s", getpid(), tmpBuff);
        }

        int nextPipe = (pipeNum + 1) % (PROCESS_COUNT + 1);

        if (feof(fp))
        {
            fclose(fp);

            write(pipefd[pipeNum - 1][1], "\0", 1);
            printf("%d Read all data\n", getpid());
            break;
        }
        write(pipefd[nextPipe][1], tmpBuff, sizeof(tmpBuff));
        fclose(fp);
    }

    wait(NULL);
    printf("%d I'm exiting...\n", getpid());
    return 0;
}

int checkOffset(char *str)
{
    str[strlen(str) - 1] = '\0';
    if (strcmp(str, "first") == 0)
        return 1;
    else if (strcmp(str, "second") == 0)
        return 2;
    else if (strcmp(str, "third") == 0)
        return 3;
    else if (strcmp(str, "fourth") == 0)
        return 4;
    else if (strcmp(str, "fifth") == 0)
        return 5;
    else if (strcmp(str, "sixth") == 0)
        return 6;
    else if (strcmp(str, "seventh") == 0)
        return 7;
    else if (strcmp(str, "eighth") == 0)
        return 8;
    else if (strcmp(str, "nineth") == 0)
        return 9;
    else if (strcmp(str, "tenth") == 0)
        return 10;
    else
        return -1;
}