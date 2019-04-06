#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Calculating time
double CalcTime(struct timeval time_begin, struct timeval time_end) {

    return (double) (time_end.tv_usec - time_begin.tv_usec) / 1000000 + (double) (time_end.tv_sec - time_begin.tv_sec);
}