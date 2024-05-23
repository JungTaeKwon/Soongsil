// #include <stdio.h>
#include "20192944.h"

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
        /*
        Pipe creation
        process #0 - process #1: pipefd[0][*]
        process #1 - process #2: pipefd[1][*]
        process #2 - process #3: pipefd[2][*]
        process #3 - process #4: pipefd[3][*]
        process #4 - process #0: pipefd[4][*]
        */
        if (pipe(pipefd[i]) == -1)
        {
            perror("[*] pipe creation error");
            exit(1);
        }
    }

    for (int i = 0; i < PROCESS_COUNT; i++)
    {
        // Create 4 child processes ONLY in process #0 (parent process)
        if (pids[0] == getpid())
        {
            // Save pid of parent process
            pids[i + 1] = fork();
            if (pids[i + 1] == 0)
            {
                // Save pid of child processes
                pids[i + 1] = getpid();
            }
        }
    }

    /*
    Save pipe index to local variable 'pipeNum'
    Each process should know which pipe index is allcoated to its process
    */
    for (int i = 0; i < PROCESS_COUNT + 1; i++)
    {
        if (pids[i] == getpid())
        {
            pipeNum = i;
        }
    }

    // Temporary buffer to get data from kernel buffer
    char tmpBuff[BUFFER_SIZE];

    // Start of file reading in process #0
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

        // Let the next process(process #1) take turns
        write(pipefd[pipeNum + 1][1], tmpBuff, sizeof(tmpBuff));
        fclose(fp);
    }

    // For every process(#0 ~ #4)
    while (1)
    {
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            perror("[*] fopen error");
            exit(1);
        }
        // Wait until previous process tells to read the buffer
        read(pipefd[pipeNum][0], tmpBuff, sizeof(tmpBuff));
        /*
        Each process get offset of the file read (line #136)
        Get integer value so current process can jump to the suitable line (line #106)
        */
        int offsetCnt = checkOffset(tmpBuff);
        if (offsetCnt == -1)
        {
            /*
            If '\0' is in the kernel buffer, checkOffset() will return -1 (line #131)
            so that current process can tell "I'm exiting, you need to exit" to previous process
            */
            write(pipefd[pipeNum - 1][1], "\0", 1);
            break;
        }
        // Jump to offset
        for (int i = 0; i < offsetCnt; i++)
        {
            fgets(tmpBuff, BUFFER_SIZE, fp);
        }
        // Read file
        fgets(tmpBuff, BUFFER_SIZE, fp);

        // Consider the last 'fgets()' (it doesn't include '\n')
        if (tmpBuff[strlen(tmpBuff) - 1] != '\n')
        {
            printf("%d %s\n", getpid(), tmpBuff);
        }
        else
        {
            printf("%d %s", getpid(), tmpBuff);
        }

        // Next pipe number
        int nextPipe = (pipeNum + 1) % (PROCESS_COUNT + 1);

        // If current process reach EOF
        if (feof(fp))
        {
            fclose(fp);
            // Tell previous process to exit
            write(pipefd[pipeNum - 1][1], "\0", 1);
            printf("%d Read all data\n", getpid());
            break;
        }
        // Toss offset of file to the next process
        write(pipefd[nextPipe][1], tmpBuff, sizeof(tmpBuff));
        fclose(fp);
    }
    // Wait for exit of child processes
    wait(NULL);
    printf("%d I'm exiting...\n", getpid());
    return 0;
}

int checkOffset(char *str)
{
    // Returns numeric value that matches str
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