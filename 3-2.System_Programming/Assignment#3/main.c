#include "mystdio.h"
#include <unistd.h>

int main()
{
    // printf("[*] 2024 System Programming, Assignment#3\n");

    // my_fopen test
    MYFILE *fp = my_fopen("sample.txt", "r");
    if (fp == NULL)
    {
        write(STDERR_FILENO, "fail\n", 5);
    }
    else
    {
        write(STDOUT_FILENO, "success\n", 8);
    }
    return 0;
}