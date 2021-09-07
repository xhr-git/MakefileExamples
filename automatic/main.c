#include <stdio.h>
#include <pthread.h>
#include "common.h"
#include "good.h"

void print_author(const char *name);

void *thread_task(void *data)
{
    printf("%s\n", __func__);
    print_good();
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t thd;
    pthread_create(&thd, NULL, thread_task, NULL);
    printf("hello\n");
    pthread_join(thd, NULL);
    print_author(AUTHOR_NAME);
    return 0;
}
