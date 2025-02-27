#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int count = 0;

void    *routine(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (count >= 10)
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
        printf("Thread %ld\n", pthread_self());
        count++;
        pthread_mutex_unlock(&mutex);
    }
    return (NULL);
}

int main(void)
{
    pthread_t thread[10];
    int i;
    i = 0;
    while (i < 10)
    {
        pthread_create(&thread[i], NULL, routine, NULL);
        i++;
    }
    i = 0;
    while (i < 10)
    {
        pthread_join(thread[i], NULL);
        i++;
    }
    return 0;
}