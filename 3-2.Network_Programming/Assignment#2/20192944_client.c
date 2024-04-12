#include "20192944_client.h"

void err_proc();
void sigintHandler(int);

int main(int argc, char **argv)
{
    int clntSd;
    struct sockaddr_in clntAddr;
    int clntAddrLen, readLen, recvByte, maxBuff;
    char rBuff[BUFSIZ];
    signal(SIGINT, sigintHandler);

    if (argc != 3)
    {
        printf("[*] Usage: %s [IP ADDR] [Port]\n", argv[0]);
    }
    clntSd = socket(AF_INET, SOCK_STREAM, 0);
    if (clntSd == -1)
        err_proc();

    memset(&clntAddr, 0, sizeof(clntAddr));
    clntAddr.sin_family = AF_INET;
    clntAddr.sin_addr.s_addr = inet_addr(argv[1]);
    clntAddr.sin_port = htons(atoi(argv[2]));

    if (connect(clntSd, (struct sockaddr *)&clntAddr,
                sizeof(clntAddr)) == -1)
    {
        close(clntSd);
        err_proc();
    }

    recv(clntSd, rBuff, BUFSIZ, 0);
    printf("%s\n", rBuff);

    while (1)
    {
        char wBuff[BUFSIZ];
        signal(SIGINT, sigintHandler);
        printf("[*] TO SERVER: ");
        fgets(wBuff, BUFSIZ - 1, stdin);
        readLen = strlen(wBuff);
        if (readLen < 2)
            continue;
        send(clntSd, wBuff, readLen - 1, 0);
        recvByte = 0;

        maxBuff = BUFSIZ - 1;
        do
        {
            recvByte += recv(clntSd, rBuff, maxBuff, 0);
            maxBuff -= recvByte;
        } while (recvByte < (readLen - 1));
        rBuff[recvByte] = '\0';

        printf("[*] FROM SERVER: %s\n\n", rBuff);

        if (strcmp(rBuff, "q") == 0)
        {
            exit(0);
        }
    }
    close(clntSd);
    clntSd = 0xffffffff;
    return 0;
}

void err_proc()
{
    fprintf(stderr, "Error: %s\n", strerror(errno));
    exit(errno);
}

void sigintHandler(int signum)
{
    printf("\n[*] SIGINT received. Ignoring...\n");
    return;
}