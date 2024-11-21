#include "types.h"
#include "stat.h"
#include "user.h"

#define PGSIZE 4096
#define ARRAY_SIZE (4*PGSIZE)  // 여러 페이지에 걸쳐 테스트

int
main(void)
{
    printf(1, "=== COW Test Start ===\n");
    
    // 1. 처음 free한 페이지 수
    int initial_pages = getNumFreePages();
    printf(1, "Initial free pages: %d\n", initial_pages);
    
    // 2. 큰 배열 할당
    char *array = malloc(ARRAY_SIZE);
    // 3. 배열 초기화
    for(int i = 0; i < ARRAY_SIZE; i++)
        array[i] = 'A';
    
    // 4. fork 전 free한 페이지 수
    printf(1, "Before fork - free pages: %d\n", getNumFreePages());
    
    // 5. fork
    int pid = fork();
    if(pid < 0){
        printf(1, "Fork failed\n");
        exit();
    }
    
    // 6. 자식 프로세스
    if(pid == 0){  
        printf(1, "Child process - free pages: %d\n", getNumFreePages());
        // 7. 메모리 수정 시도
        array[0] = 'B';  // COW 발생해야 함
        printf(1, "Child after write - free pages: %d\n", getNumFreePages());
        exit();
    } else {  // 부모 프로세스
        wait();
        printf(1, "Parent after child - free pages: %d\n", getNumFreePages());
        free(array);
    }
    
    printf(1, "Final free pages: %d\n", getNumFreePages());
    printf(1, "=== COW Test End ===\n");
    exit();
} 