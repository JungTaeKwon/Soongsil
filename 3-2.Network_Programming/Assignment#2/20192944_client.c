#include "20192944_client.h"

void err_proc();
void sigintHandler(int32_t);

int main(int argc, char **argv)
{
    char wBuff[BUFSIZ];
    char rBuff[BUFSIZ];
    int32_t clntSd;
    struct sockaddr_in clntAddr;
    int32_t clntAddrLen, readLen, recvByte, maxBuff;
    signal(SIGINT, sigintHandler);

    // USAGE
    if (argc != VALID_ARGC)
    {
        printf("[*] Usage: %s [IP ADDR] [Port]\n", argv[0]);
    }
    // Init socket
    clntSd = socket(AF_INET, SOCK_STREAM, 0);
    if (clntSd == -1)
        err_proc();

    // Init socket info with IP, PORT
    memset(&clntAddr, 0, sizeof(clntAddr));
    clntAddr.sin_family = AF_INET;
    clntAddr.sin_addr.s_addr = inet_addr(argv[1]);
    clntAddr.sin_port = htons(atoi(argv[2]));

    // TCP conn with args server & handle exception
    if (connect(clntSd, (struct sockaddr *)&clntAddr,
                sizeof(clntAddr)) == -1)
    {
        close(clntSd);
        err_proc();
    }

    // This recv() is for WELOCOME_MESSAGE from server
    recv(clntSd, rBuff, BUFSIZ, 0);
    printf("%s\n", rBuff);

    while (CONTINUE_UNTIL_QUIT)
    {
        // Init signal handler
        signal(SIGINT, sigintHandler);

        // Get input from user
        printf("[*] TO SERVER: ");
        if (!fgets(wBuff, BUFSIZ - 1, stdin))
        {
            continue;
        }

        readLen = strlen(wBuff);
        // Handle when input is plain [NEW LINE]
        if (strcmp(wBuff, "\n") == 0)
        {
            continue;
        }
        // Send to server
        send(clntSd, wBuff, readLen - 1, 0);

        // Receive and Handle the data from server
        recvByte = 0;
        maxBuff = BUFSIZ - 1;
        do
        {
            recvByte += recv(clntSd, rBuff, maxBuff, 0);

            maxBuff -= recvByte;
        } while (recvByte < (readLen - 1));
        rBuff[recvByte] = '\0';

        // Print to server console
        printf("[*] FROM SERVER: %s\n\n", rBuff);
        if (strcmp(rBuff, "q") == 0)
        {
            exit(0);
        }
    }
    close(clntSd);
    // Set max val after closing socket
    clntSd = 0xffffffff;
    return 0;
}

void err_proc()
{
    // Print handle with standard error lib
    fprintf(stderr, "Error: %s\n", strerror(errno));
    exit(errno);
}

void sigintHandler(int32_t signum)
{
    // Handle SIGINT (CTRL+C)
    printf("\n\n[*] SIGINT received. Ignoring...\n");
    printf("[*] 'q' to exit...\n\n");
    return;
}