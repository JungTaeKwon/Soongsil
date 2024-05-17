#include "20192944.h"

int main(int argc, char *argv[])
{
    pid_t pids[PROCESS_COUNT];
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror("[*]File opening failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < PROCESS_COUNT; i++)
    {
        pids[i] = fork();
        if (pids[i] < 0)
        {
            perror("[*] Fork failed");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}