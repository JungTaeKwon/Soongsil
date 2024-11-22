#include "types.h"
#include "stat.h"
#include "user.h"

#define PGSIZE 4096
#define ARRAY_SIZE (4*PGSIZE)


void getNumFreePagesTest(void){
    int free_pages = getNumFreePages();
    printf(1, "==========\n");
    printf(1, "Student ID: 20192944\n");
    printf(1, "Number of Free Pages: %d\n", free_pages);
    printf(1, "==========\n");
    exit();
}

void cowTest(void) {
    printf(1, "=== COW Test Start ===\n");
    printf(1, "Initial free pages: %d\n", getNumFreePages());
    
    char *array = malloc(ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) array[i] = 'A';
    printf(1, "Before fork - free pages: %d\n", getNumFreePages());
    
    int pid = fork();
    if (pid < 0) {
        printf(1, "Fork failed\n");
        exit();
    }
    
    if (pid == 0) {
        // Child process
        printf(1, "Child process - free pages: %d\n", getNumFreePages());
        // COW 발생
        array[0] = 'B';
        printf(1, "Child after write - free pages: %d\n", getNumFreePages());
        exit();
    } else {
        // Parent process
        wait();
        printf(1, "Parent after child - free pages: %d\n", getNumFreePages());
        free(array);
    }

    printf(1, "Final free pages: %d\n", getNumFreePages());
    printf(1, "=== COW Test End ===\n");
    exit();
}

int
main(void)
{
    // getNumFreePagesTest();
    cowTest();
}
