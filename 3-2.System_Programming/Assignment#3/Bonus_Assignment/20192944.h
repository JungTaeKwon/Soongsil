// System Programming Assignment#3 20192944 JungTae Kwon
// Simple implementation of stdio.h
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024
#define EOF -1
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define PROCESS_COUNT 5

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
    int bufpos; // current position in the buffer
    int buflen; // data len saved in the buffer
} FILE;

FILE *fopen(const char *pathname, const char *mode);
int fread(void *ptr, int size, int nmemb, FILE *stream);
int fwrite(const void *ptr, int size, int nmemb, FILE *stream);
int fflush(FILE *stream);
int fseek(FILE *stream, off_t offset, int whence);
int feof(FILE *stream);
int fclose(FILE *stream);
char *fgets(char *str, int num, FILE *stream);

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

    // Allocate memory for buffer
    fp->buffer = (char *)calloc(1, BUFSIZE);
    // For i/o buffering
    fp->bufpos = 0;
    fp->buflen = 0;

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
        // Iterative call of read()
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

    // Return read length
    return bytesRead / size;
}

int fwrite(const void *ptr, int size, int nmemb, FILE *stream)
{
    if (stream == NULL || ptr == NULL)
    {
        return 0;
    }

    const char *data = (const char *)ptr;
    int totalBytesToWrite = size * nmemb;
    int bytesWritten = 0;

    while (bytesWritten < totalBytesToWrite)
    {
        int spaceInBuffer = BUFSIZE - stream->bufpos;
        int bytesToCopy = (totalBytesToWrite - bytesWritten) < spaceInBuffer ? (totalBytesToWrite - bytesWritten) : spaceInBuffer;

        // Move to buffer and fflush when buffer is full
        // Essential than calling many syscalls such as write()
        memcpy(stream->buffer + stream->bufpos, data + bytesWritten, bytesToCopy);
        stream->bufpos += bytesToCopy;
        bytesWritten += bytesToCopy;

        // fflush buffer when buffer is full
        // and continue i/o
        if (stream->bufpos == BUFSIZE)
        {
            if (fflush(stream) == EOF) // EOF
            {
                return EOF;
            }
        }
    }

    // fflush even if the buffer is not full
    if (fflush(stream) == EOF)
    {
        return EOF;
    }

    return bytesWritten / size;
}

int fflush(FILE *stream)
{
    if (stream == NULL || stream->buffer == NULL)
        return -1;

    if (stream->bufpos > 0)
    {
        // fflush buffer data to file descriptor
        int written = write(stream->fd, stream->buffer, stream->bufpos);
        if (written < stream->bufpos)
        {
            return EOF;
        }
        // Reset pos
        stream->bufpos = 0;
    }

    return 0;
}

int fseek(FILE *stream, off_t offset, int whence)
{
    int fd = stream->fd;
    off_t new_pos;
    off_t current_pos;

    switch (whence)
    {
        // logic
        // 1. Find a new position to move with 'whence'
        // 2. Move to new position with offset(param)
    case SEEK_SET:
        new_pos = offset;
        break;
    case SEEK_CUR:
        current_pos = lseek(fd, 0, SEEK_CUR);
        new_pos = current_pos + offset;
        break;
    case SEEK_END:
        current_pos = lseek(fd, 0, SEEK_END);
        new_pos = current_pos + offset;
        break;
    default:
        return EOF;
    }
    if (lseek(fd, new_pos, SEEK_SET) == EOF)
    {
        return EOF;
    }
    stream->eof = 1;
    return 0;
}

int feof(FILE *stream)
{
    return stream->eof ? EOF : 0;
}

int fclose(FILE *stream)
{
    // fflush buffer
    fflush(stream);

    // Free allocated data
    free(stream->buffer);
    free(stream);

    return close(stream->fd);
}

char *fgets(char *str, int num, FILE *stream)
{
    if (stream == NULL || str == NULL || num <= 0)
    {
        return NULL;
    }

    int i = 0;
    while (i < num - 1) // Leave space for the null terminator
    {
        // Read one character from the stream
        char c;
        int readBytes = read(stream->fd, &c, 1);

        // Check for EOF or read error
        if (readBytes <= 0)
        {
            stream->eof = 1; // Indicate that we've hit EOF
            if (i == 0)      // If no characters were read, return NULL
            {
                return NULL;
            }
            break; // If we've read some characters before, break and add null terminator
        }

        // Store the character in the buffer
        str[i] = c;
        i++;

        // Stop if we encounter a newline character
        if (c == '\n')
        {
            break;
        }
    }

    // Null-terminate the string
    str[i] = '\0';

    // Return the buffer
    return str;
}
