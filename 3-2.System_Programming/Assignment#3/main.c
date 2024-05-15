#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>

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
    write(STDOUT_FILENO, "[*] 1. FOPEN_TEST\n", strlen("[*] 1. FOPEN_TEST\n"));
    FILE *fp = fopen("fopen_test.txt", "r+");
    if (fp == NULL)
    {
        write(STDERR_FILENO, "[*] fopen fail\n", strlen("[*] fopen fail\n"));
    }
    else
    {
        write(STDOUT_FILENO, "[*] fopen success\n", strlen("[*] fopen success\n"));
    }

    write(STDOUT_FILENO, "\n\n", 2);
    return;
}

void fread_test()
{
    write(STDOUT_FILENO, "[*] 2. FREAD_TEST\n", strlen("[*] 2. FREAD_TEST\n"));
    FILE *fp = fopen("fread_test.txt", "r+");
    // fread test
    char readBuffer[1024];

    size_t readCount = fread(readBuffer, sizeof(char), sizeof(readBuffer) - 1, fp);
    if (readCount == 0)
    {
        write(STDOUT_FILENO, "[*] fread fail\n", strlen("[*] fread fail\n"));
    }
    else
    {
        readBuffer[readCount] = '\0';
        write(STDOUT_FILENO, "[*] fread success\n", strlen("[*] fread success\n"));
        write(STDOUT_FILENO, readBuffer, readCount);
    }

    write(STDOUT_FILENO, "\n\n", 2);
    return;
}

void fwrite_test()
{
    // fwrite test
    write(STDOUT_FILENO, "[*] 3. FWRITE_TEST\n", strlen("[*] 3. FWRITE_TEST\n"));
    FILE *fp = fopen("fwrite_test.txt", "w");
    char readBuffer[1024];
    const char *writeBuffer = "written";
    int readCount = 0;

    // write(STDOUT_FILENO, "[*] Before fwrite()\n", strlen("[*] Before fwrite()\n"));
    // readCount = fread(readBuffer, sizeof(char), sizeof(readBuffer) - 1, fp);
    // if (readCount == 0)
    // {
    //     write(STDERR_FILENO, "[*] fread fail\n", strlen("[*] fread fail\n"));
    // }
    // else
    // {
    //     readBuffer[readCount] = '\0';
    //     write(STDOUT_FILENO, readBuffer, readCount);
    // }

    size_t writeCount = fwrite(writeBuffer, sizeof(char), strlen(writeBuffer), fp);
    if (writeCount == 0)
    {
        write(STDERR_FILENO, "fwrite fail\n", strlen("fwrite fail\n"));
    }
    fclose(fp);
    write(STDOUT_FILENO, "[*] After fwrite()\n", strlen("[*] After fwrite()\n"));
    fp = fopen("fwrite_test.txt", "r");
    readCount = fread(readBuffer, sizeof(char), sizeof(readBuffer) - 1, fp);
    if (readCount == 0)
    {
        write(STDERR_FILENO, "[*] fread fail\n", strlen("[*] fread fail\n"));
    }
    else
    {
        readBuffer[readCount] = '\0';
        write(STDOUT_FILENO, readBuffer, readCount);
    }

    write(STDOUT_FILENO, "\n\n", 2);
    return;
}

void fflush_test()
{
    write(STDOUT_FILENO, "[*] 4. FFLUSH_TEST\n", strlen("[*] 4. FFLUSH_TEST\n"));

    FILE *fp = fopen("fflush_test.txt", "w");
    if (fp == NULL)
    {
        write(STDERR_FILENO, "[*] fopen fail\n", strlen("[*] fopen fail\n"));
        return;
    }

    const char *text = "This is a test for fflush.\n";
    fwrite(text, sizeof(char), strlen(text), fp);

    fflush(fp);
    write(STDOUT_FILENO, "[*] fflush called\n", strlen("[*] fflush called\n"));

    fclose(fp);
    write(STDOUT_FILENO, "[*] File closed after fflush\n", strlen("[*] File closed after fflush\n"));
}

void fseek_test()
{
    write(STDOUT_FILENO, "[*] 5. FSEEK_TEST\n", strlen("[*] 5. FSEEK_TEST\n"));
    char readBuffer[1024];
    FILE *fp = fopen("fseek_test.txt", "r+");
    if (fp == NULL)
    {
        write(STDERR_FILENO, "[*] fopen fail\n", strlen("[*] fopen fail\n"));
        return;
    }

    // Test SEEK_SET
    write(STDOUT_FILENO, "[*] SEEK_SET\n", strlen("[*] SEEK_SET\n"));
    fseek(fp, 10, SEEK_SET);
    size_t readCount = fread(readBuffer, sizeof(char), sizeof(readBuffer) - 1, fp);
    if (readCount == 0)
    {
        write(STDOUT_FILENO, "[*] fread fail\n", strlen("[*] fread fail\n"));
    }
    else
    {
        readBuffer[readCount] = '\0';
        write(STDOUT_FILENO, "----------------------------------------\n", strlen("----------------------------------------\n"));
        write(STDOUT_FILENO, readBuffer, readCount);
        write(STDOUT_FILENO, "----------------------------------------\n", strlen("----------------------------------------\n"));
    }

    // Test SEEK_CUR
    fseek(fp, -10, SEEK_CUR);
    write(STDOUT_FILENO, "[*] SEEK_CUR\n", strlen("[*] SEEK_CUR\n"));
    readCount = fread(readBuffer, sizeof(char), sizeof(readBuffer) - 1, fp);
    if (readCount == 0)
    {
        write(STDOUT_FILENO, "[*] fread fail\n", strlen("[*] fread fail\n"));
    }
    else
    {
        readBuffer[readCount] = '\0';
        write(STDOUT_FILENO, "----------------------------------------\n", strlen("----------------------------------------\n"));
        write(STDOUT_FILENO, readBuffer, readCount);
        write(STDOUT_FILENO, "----------------------------------------\n", strlen("----------------------------------------\n"));
    }

    // Test SEEK_END
    write(STDOUT_FILENO, "[*] SEEK_END\n", strlen("[*] SEEK_END\n"));

    fseek(fp, -5, SEEK_END);
    readCount = fread(readBuffer, sizeof(char), sizeof(readBuffer) - 1, fp);
    if (readCount == 0)
    {
        write(STDOUT_FILENO, "[*] fread fail\n", strlen("[*] fread fail\n"));
    }
    else
    {
        readBuffer[readCount] = '\0';
        write(STDOUT_FILENO, "----------------------------------------\n", strlen("----------------------------------------\n"));
        write(STDOUT_FILENO, readBuffer, readCount);
        write(STDOUT_FILENO, "----------------------------------------\n", strlen("----------------------------------------\n"));
    }

    fclose(fp);
}

void feof_test()
{
    write(STDOUT_FILENO, "[*] 6. FEOF_TEST\n", strlen("[*] 6. FEOF_TEST\n"));
    FILE *fp = fopen("feof_test.txt", "r");
    int flag = feof(fp);
    if (flag == 0)
    {
        write(STDOUT_FILENO, "[*] feof success\n", strlen("[*] feof success\n"));
    }
    else if (flag == -1)
    {
        write(STDOUT_FILENO, "[*] feof fail\n", strlen("[*] feof fail\n"));
    }
    else
    {
        write(STDOUT_FILENO, "[*] feof success with flag\n", strlen("[*] feof success with flag\n"));
    }
}

void fclose_test()
{
    write(STDOUT_FILENO, "[*] 7. FCLOSE_TEST\n", strlen("[*] 7. FCLOSE_TEST\n"));
    FILE *fp = fopen("fclose_test.txt", "r");
    int flag = fclose(fp);

    // Check after fclose()
    if (flag == 0)
    {
        write(STDOUT_FILENO, "[*] fclose success\n", strlen("[*] fclose success\n"));
    }
    else
    {
        write(STDOUT_FILENO, "[*] fclose fail\n", strlen("[*] fclose fail\n"));
    }
}
