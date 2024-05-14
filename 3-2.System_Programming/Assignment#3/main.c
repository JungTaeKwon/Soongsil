#include "mystdio.h"
#include <unistd.h>

void fopen_test();
void fread_test();
void fwrite_test();
void fflush_test();
void fseek_test();
void feof_test();
void fclose_test();

int main()
{
    fopen_test();

    fread_test();

    fwrite_test();

    fflush_test();

    fseek_test();

    feof_test();

    fclose_test();

    return 0;
}

void fopen_test()
{
    // fopen test
    write(stdout, "[*] FOPEN_TEST\n", strlen("[*] FOPEN_TEST\n"));
    FILE *fp = fopen("fopen_test.txt", "r+");
    if (fp == NULL)
    {
        write(stderr, "[*] fopen fail\n", strlen("[*] fopen fail\n"));
    }
    else
    {
        write(stdout, "[*] fopen success\n", strlen("[*] fopen success\n"));
    }

    write(stdout, "\n\n", 2);
    return;
}

void fread_test()
{
    write(stdout, "[*] FREAD_TEST\n", strlen("[*] FREAD_TEST\n"));
    FILE *fp = fopen("fread_test.txt", "r+");
    // fread test
    char readBuffer[1024];

    size_t readCount = fread(readBuffer, sizeof(char), sizeof(readBuffer) - 1, fp);
    if (readCount == 0)
    {
        write(stdout, "[*] fread fail\n", strlen("[*] fread fail\n"));
    }
    else
    {
        readBuffer[readCount] = '\0';
        write(stdout, "[*] fread success\n", strlen("[*] fread success\n"));
        write(stdout, readBuffer, readCount);
    }

    write(stdout, "\n\n", 2);
    return;
}

void fwrite_test()
{
    // fwrite test
    write(stdout, "[*] FWRITE_TEST\n", strlen("[*] FWRITE_TEST\n"));
    FILE *fp = fopen("fwrite_test.txt", "r+");
    char readBuffer[1024];
    const char *writeBuffer = "changed text\n";
    int readCount = 0;

    write(stdout, "[*] Before fwrite()\n", strlen("[*] Before fwrite()\n"));
    readCount = fread(readBuffer, sizeof(char), sizeof(readBuffer) - 1, fp);
    if (readCount == 0)
    {
        write(stderr, "[*] fread fail\n", strlen("[*] fread fail\n"));
    }
    else
    {
        readBuffer[readCount] = '\0';
        write(stdout, readBuffer, readCount);
    }

    size_t writeCount = fwrite(writeBuffer, sizeof(char), strlen(writeBuffer), fp);
    if (writeCount == 0)
    {
        write(stderr, "fwrite fail\n", strlen("fwrite fail\n"));
    }

    write(stdout, "[*] After fwrite()\n", strlen("[*] After fwrite()\n"));
    fp = fopen("fwrite_test.txt", "r+");
    readCount = fread(readBuffer, sizeof(char), sizeof(readBuffer) - 1, fp);
    if (readCount == 0)
    {
        write(stderr, "[*] fread fail\n", strlen("[*] fread fail\n"));
    }
    else
    {
        readBuffer[readCount] = '\0';
        write(stdout, readBuffer, readCount);
    }

    write(stdout, "\n\n", 2);
    return;
}

void fflush_test()
{
}

void fseek_test()
{
    char readBuffer[1024];
    FILE *fp = fopen("fseek_test.txt", "r+");
    if (fp == NULL)
    {
        write(stderr, "[*] fopen fail\n", strlen("[*] fopen fail\n"));
        return;
    }

    // Test SEEK_SET
    fseek(fp, 10, SEEK_SET);
    size_t readCount = fread(readBuffer, sizeof(char), sizeof(readBuffer) - 1, fp);
    if (readCount == 0)
    {
        write(stdout, "[*] fread fail\n", strlen("[*] fread fail\n"));
    }
    else
    {
        readBuffer[readCount] = '\0';
        write(stdout, "----------------------------------------\n", strlen("----------------------------------------\n"));
        write(stdout, readBuffer, readCount);
        write(stdout, "----------------------------------------\n", strlen("----------------------------------------\n"));
    }

    // Test SEEK_CUR
    fseek(fp, -10, SEEK_CUR);
    readCount = fread(readBuffer, sizeof(char), sizeof(readBuffer) - 1, fp);
    if (readCount == 0)
    {
        write(stdout, "[*] fread fail\n", strlen("[*] fread fail\n"));
    }
    else
    {
        readBuffer[readCount] = '\0';
        write(stdout, "----------------------------------------\n", strlen("----------------------------------------\n"));
        write(stdout, readBuffer, readCount);
        write(stdout, "----------------------------------------\n", strlen("----------------------------------------\n"));
    }

    // Test SEEK_END
    fseek(fp, -5, SEEK_END);
    readCount = fread(readBuffer, sizeof(char), sizeof(readBuffer) - 1, fp);
    if (readCount == 0)
    {
        write(stdout, "[*] fread fail\n", strlen("[*] fread fail\n"));
    }
    else
    {
        readBuffer[readCount] = '\0';
        write(stdout, "----------------------------------------\n", strlen("----------------------------------------\n"));
        write(stdout, readBuffer, readCount);
        write(stdout, "----------------------------------------\n", strlen("----------------------------------------\n"));
    }

    fclose(fp);
}

void feof_test()
{
    FILE *fp = fopen("feof_test.txt", "r");
    feof(fp);
    if (fp->eof == 0)
    {
        write(stdout, "[*] feof success\n", strlen("[*] feof success\n"));
    }
    else if (fp->eof == -1)
    {
        write(stdout, "[*] feof fail\n", strlen("[*] feof fail\n"));
    }
    else
    {
        write(stdout, "[*] feof success with flag\n", strlen("[*] feof success with flag\n"));
    }
}

void fclose_test()
{
    FILE *fp = fopen("fclose_test.txt", "r");
    fclose(fp);

    // Use after fclose()
    char readBuffer[1024];

    size_t readCount = fread(readBuffer, sizeof(char), sizeof(readBuffer) - 1, fp);
    if (readCount == 0)
    {
        write(stdout, "[*] fclose success\n", strlen("[*] fclose success\n"));
    }
    else
    {
        write(stdout, "[*] fclose fail\n", strlen("[*] fclose fail\n"));
    }
}