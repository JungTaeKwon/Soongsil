#include "20192944_server.h"

void errProc(const char *);
int32_t calculate(int32_t, int32_t, char *, char *, sockaddr_in);

int main(int argc, char **argv)
{
    int srvSd, clntSd;
    sockaddr_in srvAddr, clntAddr;
    int clntAddrLen, readLen, strLen;

    pid_t pid;

    if (argc != 2)
    {
        printf("[*] Usage: %s [port] \n", argv[0]);
        exit(1);
    }
    printf("[*] Server start...\n");

    srvSd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // Handle socket exception
    if (srvSd == -1)
        errProc("[*] ERROR");

    // Init socket info
    memset(&srvAddr, 0, sizeof(srvAddr));
    srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port = htons(atoi(argv[1]));

    // Allocate IP and PORT with bind()
    if (bind(srvSd, (struct sockaddr *)&srvAddr, sizeof(srvAddr)) == -1)
        errProc("[*] ERROR");
    if (listen(srvSd, 5) < 0)
        errProc("[*] ERROR");
    clntAddrLen = sizeof(clntAddr);

    while (1)
    {
        // Connect with client
        clntSd = accept(srvSd, (struct sockaddr *)&clntAddr, &clntAddrLen);
        if (clntSd == -1)
        {
            errProc("[*] ERROR");
            continue;
        }
        printf("[*] Client %s:%d is connected...\n",
               inet_ntoa(clntAddr.sin_addr),
               ntohs(clntAddr.sin_port)); // NBO (serialization)
        pid = fork();
        if (pid == 0)
        { // Child process for each client
            close(srvSd);
            // Send WELCOME_MESSAGE
            send(clntSd, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE), 0);
            while (1)
            {
                // Send ENU
                send(clntSd, MENU, strlen(MENU), 0);
                // Init buffer for READ/WRITE
                char rBuff[BUFSIZ];
                char wBuff[BUFSIZ];

                // RECV
                readLen = recv(clntSd, rBuff, BUFSIZ - 1, 0);
                if (readLen == 0)
                    break;
                rBuff[readLen] = '\0';
                printf("[*] Received From Client(#%d): %s\n",
                       ntohs(clntAddr.sin_port), rBuff);

                // Case[1]: Time info
                if (strcmp(rBuff, "1") == 0)
                {
                    time_t timer;
                    time(&timer);
                    send(clntSd, ctime(&timer), strlen(ctime(&timer)), 0);
                }
                // Case[2]: Calculator
                else if (strcmp(rBuff, "2") == 0)
                {
                    if (calculate(clntSd, readLen, rBuff, wBuff, clntAddr))
                    {
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                // Case[q]: QUIT
                else if (strcmp(rBuff, "q") == 0)
                {
                    memcpy(wBuff, rBuff, strlen(rBuff));
                    send(clntSd, wBuff, strlen(rBuff), 0);
                    break;
                }
                // CaseE{ANY_TEXT}: ECHO
                else
                {
                    memcpy(wBuff, rBuff, strlen(rBuff));
                    wBuff[strlen(rBuff)] = '\0';
                    send(clntSd, wBuff, strlen(wBuff), 0);
                }
            }
            // Disconnect
            printf("[*] Client(%d): disconnected\n",
                   ntohs(clntAddr.sin_port)); // NBO (serialization)
            close(clntSd);
            return 0;
        }
        else if (pid == -1)
            errProc("fork");
        else
        { // Parent process
            close(clntSd);
        }
    }
    close(srvSd);
    return 0;
}

void errProc(const char *str)
{
    fprintf(stderr, "%s: %s \n", str, strerror(errno));
    exit(1);
}

int32_t calculate(int32_t clntSd, int32_t readLen, char *rBuff, char *wBuff, sockaddr_in clntAddr)
{
    float32_t a, b, result;
    char operator;

    send(clntSd, CALCULATOR_MENU, strlen(CALCULATOR_MENU), 0);

    readLen = recv(clntSd, rBuff, BUFSIZ - 1, 0);
    if (readLen == 0)
        return BREAK;
    rBuff[readLen] = '\0';
    printf("[*] Client(%d): %s\n",
           ntohs(clntAddr.sin_port), rBuff);

    sscanf(rBuff, "%f %c %f", &a, &operator, & b);
    switch (operator)
    {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
        if (a == 0 || b == 0)
        {
            strcpy(rBuff, "[Error: Division by zero]");
            if (write(clntSd, rBuff, strlen(rBuff)) < 0)
            {
                perror("[Error writing to socket]");
            }
            return CONTINUE;
        }
        else
        {
            result = a / b;
        }
        break;
    default:
        strcpy(wBuff, "[Error: Invalid operator]");
        if (write(clntSd, wBuff, strlen(wBuff)))
        {
            perror("[Error writing to socket]");
        }
        return CONTINUE;
    }
    sprintf(wBuff, "[ %.2f %c %.2f = %.2f ]", a, operator, b, result);

    send(clntSd, wBuff, strlen(wBuff), 0);
}