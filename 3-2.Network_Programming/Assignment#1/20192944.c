#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>

#define MAX_URL_LENGTH 100

void printUsage(const char *programName)
{
    printf("[*] Usage: %s {URL}\n", programName);
}

void printAddressInfo(const struct addrinfo *const address_list)
{
    printf("[*] Resolve IP addr from domain name..\n");

    // 주소 값이 담겨있는 linked list를 순회하며 출력
    const struct addrinfo *p;
    for (p = address_list; p != NULL; p = p->ai_next)
    {
        void *addr;
        const char *ipver;

        if (p->ai_family == AF_INET)
        { // Case: IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        }
        else
        { // Case: IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        char ipstr[INET6_ADDRSTRLEN];
        // nbo 직렬화
        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf("[*] %s: %s\n", ipver, ipstr);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printUsage(argv[0]);
        return 1;
    }

    char url[MAX_URL_LENGTH];
    // argument input 복사 처리
    strncpy(url, argv[1], MAX_URL_LENGTH - 1);
    // 문자열 끝처리
    url[MAX_URL_LENGTH - 1] = '\0';

    // getaddrinfo() 반환 값 필터링을 위한 변수 hints
    struct addrinfo hints;
    // getaddrinfo() 반환 값을 받을 linked list
    struct addrinfo *address_list;

    memset(&hints, 0, sizeof(hints));
    // Accept IPv4, IPv6
    hints.ai_family = AF_UNSPEC;
    // Only TCP
    hints.ai_socktype = SOCK_STREAM;

    // getaddrinfo() 호출 중 문제 발생 시 예외처리
    if (getaddrinfo(url, NULL, &hints, &address_list) != 0)
    {
        printf("[*] Error occured..");
        return 1;
    }

    printAddressInfo(address_list);
    freeaddrinfo(address_list);

    return 0;
}
