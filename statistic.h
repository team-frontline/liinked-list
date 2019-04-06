#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//float *values[];
float calculate_mean(float values[], int n)
{
    float total = 0;
    for (int i = 0; i < n; i++)
    {
        total += values[i];
    }
    return total / n;
}

float calculate_std(float values[], int n)
{
    float mean = calculate_mean(values, n);
    float total = 0;
    for (int i = 0; i < n; i++)
    {
        total += ((values[i] - mean) * (values[i] - mean));
    }
    return sqrt(total / n);
}

float number_of_times(float values[], int n, float z, float r){
    float std = calculate_std(values, n);
    float mean = calculate_mean(values, n);
    return (100*z*std/(r*mean))*(100*z*std/(r*mean));
}
