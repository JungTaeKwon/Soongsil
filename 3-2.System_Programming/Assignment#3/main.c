#include "mystdio.h"
#include <unistd.h>

void fopen_test();
void fread_test();
void fwrite_test();

int main()
{
    fopen_test();

    fread_test();

    fwrite_test();

    return 0;
}

void fopen_test()
{
    // my_fopen test
    write(stdout, "[*] MY_FOPEN_TEST\n", strlen("[*] MY_FOPEN_TEST\n"));
    MYFILE *fp = my_fopen("fopen_test.txt", "r+");
    if (fp == NULL)
    {
        write(stderr, "my_fopen fail\n", 14);
    }
    else
    {
        write(stdout, "my_fopen success\n", strlen("my_fopen success\n"));
    }

    write(stdout, "\n\n", 2);
    return;
}

void fread_test()
{
    write(stdout, "[*] MY_FREAD_TEST\n", strlen("[*] MY_FREAD_TEST\n"));
    MYFILE *fp = my_fopen("fread_test.txt", "r+");
    // my_fread test
    char readBuffer[1024];

    size_t readCount = my_fread(readBuffer, sizeof(char), sizeof(readBuffer) - 1, fp);
    if (readCount == 0)
    {
        write(stdout, "my_fread fail\n", 14);
    }
    else
    {
        readBuffer[readCount] = '\0';
        write(stdout, "my_fread success\n", 17);
        write(stdout, readBuffer, readCount);
    }

    write(stdout, "\n\n", 2);
    return;
}

void fwrite_test()
{
    // my_fwrite test
    write(stdout, "[*] MY_FWRITE_TEST\n", strlen("[*] MY_FWRITE_TEST\n"));
    MYFILE *fp = my_fopen("fwrite_test.txt", "r+");
    char readBuffer[1024];
    const char *writeBuffer = "changed text\n";
    int readCount = 0;

    write(stdout, "[*] Before my_fwrite()\n", strlen("[*] Before my_fwrite()\n"));
    readCount = my_fread(readBuffer, sizeof(char), sizeof(readBuffer) - 1, fp);
    if (readCount == 0)
    {
        write(stderr, "my_fread fail\n", strlen("my_fread fail\n"));
    }
    else
    {
        readBuffer[readCount] = '\0';
        write(stdout, readBuffer, readCount);
    }

    size_t writeCount = my_fwrite(writeBuffer, sizeof(char), strlen(writeBuffer), fp);
    if (writeCount == 0)
    {
        write(stderr, "my_fwrite fail\n", strlen("my_fwrite fail\n"));
    }

    write(stdout, "[*] After my_fwrite()\n", strlen("[*] After my_fwrite()\n"));
    fp = my_fopen("fwrite_test.txt", "r+");
    readCount = my_fread(readBuffer, sizeof(char), sizeof(readBuffer) - 1, fp);
    if (readCount == 0)
    {
        write(stderr, "my_fread fail\n", strlen("my_fread fail\n"));
    }
    else
    {
        readBuffer[readCount] = '\0';
        write(stdout, readBuffer, readCount);
    }

    write(stdout, "\n\n", 2);
    return;
}