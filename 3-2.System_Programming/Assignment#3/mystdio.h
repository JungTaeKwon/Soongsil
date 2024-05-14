#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFSIZE 1024
#define EOF -1
#define stdin 1
#define stdout 2
#define stderr 3
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

typedef struct myFile
{
    int fd;
    int pos;
    int size;
    int mode;
    int flag;
    char lastop;
    int eof;
    char *buffer;
} FILE;

FILE *fopen(const char *pathname, const char *mode)
{
    int flags;
    if (strcmp(mode, "r") == 0)
    {
        flags = O_RDONLY;
    }
    else if (strcmp(mode, "r+") == 0)
    {
        flags = O_RDWR;
    }
    else if (strcmp(mode, "w") == 0)
    {
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    }
    else if (strcmp(mode, "w+") == 0)
    {
        flags = O_RDWR | O_CREAT | O_TRUNC;
    }
    else if (strcmp(mode, "a") == 0)
    {
        flags = O_WRONLY | O_APPEND | O_CREAT | O_TRUNC;
    }
    else if (strcmp(mode, "a+") == 0)
    {
        flags = O_RDWR | O_WRONLY | O_APPEND | O_CREAT | O_TRUNC;
    }
    else
    {
        return NULL;
    }

    int fd = open(pathname, flags, 0644);
    if (fd == -1)
    {
        return NULL;
    }

    FILE *fp = (FILE *)calloc(1, sizeof(FILE));
    fp->fd = fd;
    return fp;
}

int fread(void *ptr, int size, int nmemb, FILE *stream)
{
    if (stream == NULL || ptr == NULL)
    {
        return 0;
    }

    int totalBytesToRead = size * nmemb;
    int bytesRead = 0;
    char *buffPtr = (char *)ptr;

    while (bytesRead < totalBytesToRead)
    {
        int result = read(stream->fd, buffPtr + bytesRead, totalBytesToRead - bytesRead);
        if (result < 0)
        {
            stream->eof = 1;
            break;
        }
        else if (result == 0)
        {
            stream->eof = 1;
            break;
        }
        else
        {
            bytesRead += result;
        }
    }

    return bytesRead / size;
}

int fwrite(const void *ptr, int size, int nmemb, FILE *stream)
{
    if (stream == NULL || ptr == NULL)
    {
        return 0;
    }

    int totalBytesToWrite = size * nmemb;
    int bytesWritten = 0;
    const char *buffPtr = (const char *)ptr;

    while (bytesWritten < totalBytesToWrite)
    {
        int result = write(stream->fd, buffPtr + bytesWritten, totalBytesToWrite - bytesWritten);
        if (result < 0)
        {
            break;
        }
        else
        {
            bytesWritten += result;
        }
    }

    return bytesWritten / size;
}

int fflush(FILE *stream)
{
    return 0;
}

int fseek(FILE *stream, int offset, int whence)
{
    return 0;
}

int feof(FILE *stream)
{
    return 0;
}

int fclose(FILE *stream)
{
    return 0;
}