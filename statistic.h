#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//float *values[];
float calculate_mean(double values[], int n)
{
    double total = 0;
    for (int i = 0; i < n; i++)
    {
        total += values[i];
    }
    return total / n;
}

float calculate_std(double values[], int n)
{
    float mean = calculate_mean(values, n);
    float total = 0;
    for (int i = 0; i < n; i++)
    {
        total += ((values[i] - mean) * (values[i] - mean));
    }
    return sqrt(total / n);
}

//set z=1.96 and r=5 for accuracy of ±5% and 95% confidence level
float sample_size(double values[], int n, float z, float r){
    float std = calculate_std(values, n);
    float mean = calculate_mean(values, n);
    return (100*z*std/(r*mean))*(100*z*std/(r*mean));
}
