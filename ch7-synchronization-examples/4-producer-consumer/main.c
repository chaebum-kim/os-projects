/* main.c
** Usage: ./main sleep_length(sec) #_of_producer_threads #_of_consumer_threads\n
*/

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "buffer.h"

// Worker functions
void *producer(void *param);
void *consumer(void *param);

int main(int argc, char *argv[])
{
    pthread_t *consumers = NULL, *producers = NULL;
    int sleep_sec, con_len, prod_len;

    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./main sleep_length(sec) #_of_producer_threads #_of_consumer_threads\n");
        return 1;
    }

    // Get command line arguments
    sleep_sec = atoi(argv[1]);
    con_len = atoi(argv[2]);
    prod_len = atoi(argv[3]);

    // Initialize buffer
    init_buffer();

    // Create producer threads
    producers = (pthread_t *)malloc(sizeof(pthread_t) * prod_len);
    for (int i = 0; i < prod_len; i++)
        pthread_create(&(producers[i]), NULL, producer, NULL);

    // Create consumer threads
    consumers = (pthread_t *)malloc(sizeof(pthread_t) * con_len);
    for (int i = 0; i < con_len; i++)
        pthread_create(&(consumers[i]), NULL, consumer, NULL);

    // Sleep
    sleep(sleep_sec);

    // Exit
    for (int i = 0; i < prod_len; i++)
        pthread_cancel(producers[i]);
    for (int i = 0; i < con_len; i++)
        pthread_cancel(consumers[i]);
    free(producers);
    free(consumers);

    return 0;
}

void *producer(void *param)
{
    buffer_item item;

    while (1)
    {
        sleep(1);
        item = rand();
        if (insert_item(item) < 0)
            fprintf(stderr, "Insertion Failed.");
        else
            printf("Producer produced %d\n", item);
    }
}

void *consumer(void *param)
{
    buffer_item item;

    while (1)
    {
        sleep(1);
        if (remove_item(&item) < 0)
            fprintf(stderr, "Removal Failed.");
        else
            printf("Consumer consumed %d\n", item);
    }
}