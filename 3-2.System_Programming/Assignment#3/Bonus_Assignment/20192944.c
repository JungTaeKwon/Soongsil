#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define BUFSIZE 1024
#define EOF -1
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define PROCESS_COUNT 2

int checkOffset(char *str);

int main(int argc, char *argv[])
{
    pid_t pids[PROCESS_COUNT];

    int pipefd[5][2];
    for (int i = 0; i < 5; i++)
    {
        if (pipe(pipefd[i]) == -1)
        {
            perror("[*] pipe");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 1; i++)
    {
        pids[i] = fork();
        if (pids[i] < 0)
        {
            perror("[*] Fork failed");
            exit(EXIT_FAILURE);
        }

        if (pids[i] == 0)
        {
            // Child process code
            FILE *fp = fopen(argv[1], "r");
            if (fp == NULL)
            {
                perror("[*] File opening failed");
                exit(EXIT_FAILURE);
            }

            char offset[1024];
            read(pipefd[i][0], offset, sizeof(offset));
            int iter = checkOffset(offset);

            char *location;
            char buffer[1024];
            while (iter--)
                location = fgets(buffer, BUFSIZE, fp);

            fgets(buffer, BUFSIZE, fp);
            pids[i] = getpid();
            printf("%d %s\n", pids[i], buffer);

            if (feof(fp))
            {
                printf("%d Read all data\n", pids[i]);
                exit(0);
            }

            close(pipefd[i][1]);
            fclose(fp);
        }
        else
        {
            // Parent process code
            FILE *fp = fopen(argv[1], "r");
            if (fp == NULL)
            {
                perror("[*] File opening failed");
                exit(EXIT_FAILURE);
            }

            close(pipefd[i][0]); // 읽기 끝 닫기
            char buffer[BUFSIZE];
            char *offset = fgets(buffer, BUFSIZE, fp);
            if (offset != NULL)
            {
                printf("%d %s\n", getpid(), buffer);
            }

            write(pipefd[i][1], offset, sizeof(offset));
            fclose(fp);
            close(pipefd[i][1]); // 쓰기 끝 닫기
        }
    }

    for (int i = 0; i < PROCESS_COUNT - 1; i++)
    {
        int status;
        pid_t pid = waitpid(pids[i], &status, 0);
        printf("%d I'm exiting...\n", pid);
    }
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
