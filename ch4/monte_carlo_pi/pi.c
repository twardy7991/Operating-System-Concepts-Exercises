#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define POINTS 100000

double *get_random(int min, int max);
int is_in(double x, double y);

/* program aims to calculate the value of pi with monte carlo method */
int main(void){

    double **arr = malloc(POINTS * sizeof(double *));
    int in = 0;

    for (int i = 0; i < POINTS; i++){
        arr[i] = get_random(0, 1);
    }

    for (int i = 0; i < POINTS; i++){
        double *cord = arr[i];

        if (is_in(cord[0], cord[1])){
            in += 1;
        }   
    }

    printf("counted %i\n", in);
    printf("pi approximation %lf \n", 4.0 * in / POINTS);

    return 0;
}

double *get_random(int min, int max){

    double *cord = malloc(2 * sizeof(double *));

    cord[0] = min + (max - min) * ((double)rand() / RAND_MAX);
    cord[1] = min + (max - min) * ((double)rand() / RAND_MAX);

    return cord;
}

int is_in(double x, double y){
    double sum = pow(x, 2) + pow(y, 2);
    printf("sum %lf\n", sum);
    if (sum <= 1){
        return 1;
    }
    return 0;
}