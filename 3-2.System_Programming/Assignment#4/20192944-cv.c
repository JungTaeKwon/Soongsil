#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define THREADS 4
#define N 3000

int primes[N];
int pflag[N];
int total = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;
int data = 0;

int is_prime(int v)
{
    int i;
    int bound = floor(sqrt((double)v)) + 1;
    for (i = 2; i < bound; i++)
    {
        /* No need to check against known composites */
        if (!pflag[i])
            continue;
        if (v % i == 0)
        {
            pflag[v] = 0;
            return 0;
        }
    }
    return (v > 1);
}

void *work(void *arg)
{
    int start;
    int end;
    int i;
    start = (N / THREADS) * (*(int *)arg);
    end = start + N / THREADS;
    for (i = start; i < end; i++)
    {
        if (is_prime(i))
        {
            // Lock shared mem space
            // waiter
            pthread_mutex_lock(&mutex);
            while (data)
            {
                pthread_cond_wait(&cond, &mutex);
            }
            // take action
            primes[total] = i;
            total++;
            data = 1;
            // Unlock shared mem space
            pthread_mutex_unlock(&mutex);

            // Wake other thread
            // signaler
            pthread_mutex_lock(&mutex);
            // modify d
            data = 0;
            // send signal
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mutex);
        }
    }
    return NULL;
}

int main(int argn, char **argv)
{
    int i;
    pthread_t tids[THREADS - 1];
    // array to save offset
    int thread_ids[THREADS - 1];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    for (i = 0; i < N; i++)
    {
        pflag[i] = 1;
    }
    for (i = 0; i < THREADS - 1; i++)
    {
        // Save offset
        thread_ids[i] = i;
        pthread_create(&tids[i], NULL, work, (void *)&thread_ids[i]);
    }

    i = THREADS - 1;
    work((void *)&i);

    // Wait for all threads to finish
    for (i = 0; i < THREADS - 1; i++)
    {
        pthread_join(tids[i], NULL);
    }

    printf("Number of prime numbers between 2 and %d: %d\n",
           N, total);
    for (i = 0; i < total; i++)
    {
        printf("%d\n", primes[i]);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}