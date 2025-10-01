#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

struct BasicArgs {
    int n;
    int *arr;
};

struct Args {
    struct BasicArgs args; 
    int *p;
};

void* get_max(void *arg);
void* get_min(void *arg);
void* get_avg(void *arg);

int main(int argc, char *argv[])
{   
    int *arr = malloc(4 * (argc - 1));
    int max_val;
    int min_val;
    int avg_val;

    pthread_t min_thread;
    pthread_t max_thread;
    pthread_t avg_thread;

    if (argc <= 1) {
        fprintf(stderr, "no args provided\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++){
        int n;
        if ((n = sscanf(argv[i], "%i", &arr[i-1])) != 1){
            fprintf(stderr, "could not parse arg %s", argv[i]);
        } else {
        printf("%i: %i ", i, arr[i-1]);
        }
    }

    printf("\n");

    struct BasicArgs args = {
        .n = argc - 1,
        .arr = arr,
    };
 
    struct Args max_args = {
        .args = args,
        .p = &max_val,
    };

    struct Args min_args = {
        .args = args,
        .p = &min_val,
    };

    struct Args avg_args = {
        .args = args,
        .p = &avg_val,
    };

    pthread_create(&max_thread, NULL, get_max, &max_args);
    pthread_create(&min_thread, NULL, get_min, &min_args);
    pthread_create(&avg_thread, NULL, get_avg, &avg_args);

    pthread_join(max_thread, NULL);
    pthread_join(min_thread, NULL);
    pthread_join(avg_thread, NULL);

    printf("max value: %d \nmin_value: %d, \navg_value: %d\n", max_val, min_val, avg_val);
    return 0;
}

void* get_max(void *arg)
{   
    struct Args *args = arg;
    int *arr = args->args.arr;
    int n = args->args.n;
    int *p = args->p;

    int max = -1 * (int)(pow(2, 30) - 1);
    
    for (int i = 0; i < n; i++){
        if (max < arr[i]){
            max = arr[i];
        }
    }
    
    *p = max; 
    return NULL;
}

void* get_min(void *arg)
{   
    struct Args *args = arg;
    int *arr = args->args.arr;
    int n = args->args.n;
    int *p = args->p;

    int min = (int)(pow(2, 30) - 1);

    for (int i = 0; i < n; i++){
        if (min > arr[i]){
            min = arr[i];
        }
    }
    
    *p = min; 
    return NULL;
}

void* get_avg(void *arg)
{   
    struct Args *args = arg;
    int *arr = args->args.arr;
    int n = args->args.n;
    int *p = args->p;
    int sum = 0; 

    for (int i = 0; i < n; i++){
            sum = sum + arr[i];
    }
    
    *p = sum / n; 
    return NULL;
}