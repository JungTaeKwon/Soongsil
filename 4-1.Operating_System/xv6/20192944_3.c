#define PROCESSNUM 10

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

// 원자성 보장 로깅 함수
void atomic_write_pid(int fd, int pid)
{
    char buf[32];
    int i = 0;

    // PID를 문자열로 변환
    if (pid == 0)
    {
        buf[i++] = '0';
    }
    else
    {
        int temp = pid;
        int length = 0;

        // 자릿수 계산
        while (temp > 0)
        {
            temp /= 10;
            length++;
        }

        // 버퍼에 PID를 역순으로 저장
        for (int j = length - 1; j >= 0; j--)
        {
            buf[j] = '0' + (pid % 10);
            pid /= 10;
        }
        i += length;
    }

    // " is running\n" 문자열 추가
    const char *suffix = " is running\n";
    for (int j = 0; suffix[j] != '\0'; j++)
    {
        buf[i++] = suffix[j];
    }

    // 원자적으로 파일에 기록
    write(fd, buf, i);
}

// 로그 파일의 각 프로세스 별 실행 횟수 통계 출력하는 함수
void print_process_counts(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        printf(1, "파일 열기 실패\n");
        return;
    }

    // 각 PID의 실행 횟수를 저장할 배열
    int counts[PROCESSNUM * 2];
    for (int i = 0; i < PROCESSNUM * 2; i++)
    {
        counts[i] = 0;
    }

    char buf[64];
    int n;

    // 파일에서 한 번에 읽어와서 처리
    while ((n = read(fd, buf, sizeof(buf))) > 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (buf[i] >= '0' && buf[i] <= '9')
            {
                // PID 숫자를 읽기
                int pid = 0;
                while (i < n && buf[i] >= '0' && buf[i] <= '9')
                {
                    pid = pid * 10 + (buf[i] - '0');
                    i++;
                }
                // 실행 횟수 증가
                counts[pid]++;
            }
        }
    }
    close(fd);

    // 실행 결과 출력
    for (int i = 0; i < PROCESSNUM * 2; i++)
    {
        if (counts[i] > 0)
        {
            printf(1, "process %d: %d times\n", i, counts[i]);
        }
    }
}

int main(void)
{
    int fd;
    char *filename = "log.txt";

    // 로그 파일 생성
    fd = open(filename, O_CREATE | O_WRONLY);
    if (fd < 0)
    {
        printf(1, "파일 열기 실패\n");
        exit();
    }

    int pid;
    int child_pids[PROCESSNUM];

    // 부모 프로세스는 자식 프로세스 10개를 생성
    for (int i = 0; i < PROCESSNUM; i++)
    {
        pid = fork();

        if (pid == 0)
        {
            // 1~10 사이의 priority를 갖는 프로세스 10개 생성
            int current_pid = getpid();
            set_proc_priority(current_pid, i + 1);

            // int current_priority = get_proc_priority(current_pid);

            while (1)
            {
                // int new_priority = get_proc_priority(current_pid);
                // if (new_priority != current_priority)
                // {
                //     atomic_write_pid(fd, current_pid);
                //     current_priority = new_priority;
                // }
                atomic_write_pid(fd, current_pid);
            }
        }

        {
            child_pids[i] = pid; // 자식 PID를 저장 (나중에 kill하기 위해)
            printf(1, "[*] PID[%d] Saved..\n", pid);
        }
    }

    // 20초(2000tic) 대기 후 자식 프로세스 모두 kill
    sleep(2000);

    for (int i = 0; i < PROCESSNUM; i++)
    {
        printf(1, "[*] Kill PID[%d] Proc..\n", child_pids[i]);
        kill(child_pids[i]);
    }

    // 자식 프로세스들이 kill을 받고 죽도록 기다리기
    for (int i = 0; i < PROCESSNUM; i++)
    {
        wait();
    }

    // 자식 프로세스들에서 저장한 로그 파일 통계내서 출력
    print_process_counts(filename);

    exit();
}
