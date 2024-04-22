#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

#define WELCOME_MESSAGE "[*] WELCOME TO 20192944_ASSIGNMENT#2_SERVER\n"
#define MENU "\n\n        MENU        \n**********************\n* 1. Current time (1)*\n* 2. Calculator   (2)*\n* 3. Quit         (q)*\n* 4. ECHO  {ANY_TEXT}*\n**********************\n"
#define CALCULATOR_MENU "ADD[+], SUB[-], MUL[*], DIV[/]"
#define CALCULATION_ENTER "[*]Please enter a calculation formula"
#define sockaddr_in struct sockaddr_in

#define float32_t float

#define CONTINUE 1
#define BREAK 0
#define VALID_ARGC 2
#define CONTINUE_UNTIL_CLIENT_QUIT 1