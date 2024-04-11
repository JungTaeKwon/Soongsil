#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

void print_minios(char *str);
void student_info();
extern int fork_exec();

int main()
{
    print_minios("[MiniOS SSU] Hello, World!");

    char *input;

    while (1)
    {
        // readline을 사용하여 입력 받기
        input = readline("커맨드를 입력하세요(종료:exit) : ");

        if (strcmp(input, "exit") == 0)
        {
            break;
        }
        if (strcmp(input, "student_info") == 0)
        {
            student_info();
            continue;
        }
        if (strcmp(input, "fork_exec") == 0)
        {
            fork_exec();
            continue;
        }
        // 입력받은 커맨드 실행
        system(input);
    }

    // 메모리 해제
    free(input);
    print_minios("[MiniOS SSU] MiniOS Shutdown........");

    return (1);
}

void print_minios(char *str)
{
    printf("%s\n", str);
}

void student_info()
{
    printf("20192944_JungTae_Kwon\n");
}
