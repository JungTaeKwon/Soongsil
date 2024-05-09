#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

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
} MYFILE;

MYFILE *my_fopen(const char *pathname, const char *mode)
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
        flags = O_WRONLY | (O_CREAT | O_TRUNC);
    }
    else if (strcmp(mode, "w+") == 0)
    {
        flags = O_RDWR | (O_CREAT | O_TRUNC);
    }
    else if (strcmp(mode, "a") == 0)
    {
        flags = (O_WRONLY | O_APPEND) | (O_CREAT | O_TRUNC);
    }
    else if (strcmp(mode, "a+") == 0)
    {
        flags = O_RDWR | (O_WRONLY | O_APPEND) | (O_CREAT | O_TRUNC);
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

    MYFILE *fp = (MYFILE *)malloc(sizeof(MYFILE));
    fp->fd = fd;
    return fp;
}
