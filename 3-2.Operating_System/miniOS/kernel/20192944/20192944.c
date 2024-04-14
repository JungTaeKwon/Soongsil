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