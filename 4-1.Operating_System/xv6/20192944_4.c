#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
    int free_pages = getNumFreePages();
    printf(1, "==========\n");
    printf(1, "Student ID: 20192944\n");
    printf(1, "Number of Free Pages: %d\n", free_pages);
    printf(1, "==========\n");
    exit();
} 