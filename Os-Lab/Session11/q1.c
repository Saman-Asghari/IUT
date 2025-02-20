#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 4
//struct for passing the data to the thread
typedef struct {
    int *vector1;
    int *vector2;
    int start_idx;
    int end_idx;
} threaddata;

sem_t semaphore;
long long int dot_product = 0;

void *computePartialSum(void *arg)
{
    threaddata *data = (threaddata *)arg;
    int partial_sum = 0;
    for (int i = data->start_idx; i < data->end_idx; i++)
    {
        partial_sum += data->vector1[i] * data->vector2[i];
    }
    sem_wait(&semaphore);
    dot_product += partial_sum;
    sem_post(&semaphore);
    pthread_exit(NULL);
}

int main()
{
    sem_init(&semaphore, 0, 1);
    pthread_t thread_pool[NUM_THREADS];
    threaddata thread_data[NUM_THREADS];
    int vector_size;
    printf("Enter the size of the vectors:");
    scanf("%d", &vector_size);
    int *vector1 = (int *)malloc(vector_size * sizeof(int));
    int *vector2 = (int *)malloc(vector_size * sizeof(int));
    printf("vector number 1:\n");
    for (int i = 0; i < vector_size; i++)
    {
        printf("vector1[%d]:", i);
        scanf("%d", &vector1[i]);
    }
    printf("vector number 2:\n");
    for (int i = 0; i < vector_size; i++)
    {
        printf("vector2[%d]: ", i);
        scanf("%d", &vector2[i]);
    }
    int chunk_size = vector_size / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_data[i].vector1 = vector1;
        thread_data[i].vector2 = vector2;
        thread_data[i].start_idx = i * chunk_size;
        if (i == NUM_THREADS - 1)
        {
            thread_data[i].end_idx = vector_size;
        }
        else
        {
            thread_data[i].end_idx = (i + 1) * chunk_size;
        }
        pthread_create(&thread_pool[i], NULL, computePartialSum, (void *)&thread_data[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(thread_pool[i], NULL);
    }
    printf("inner equals: %lld\n", dot_product);

    free(vector1);
    free(vector2);

    return 0;
}