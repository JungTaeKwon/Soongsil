#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define NUM_THREADS 10
#define TOTAL_POINTS 100000000

int points_in_circle = 0;
pthread_mutex_t mutex;

#define MAX_PROCESSES 10

struct Process
{
    int id;
    int burst_time;
    int remaining_time;
};