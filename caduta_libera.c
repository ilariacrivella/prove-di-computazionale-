#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define G 9.81
#define M 1.00

void euler_step(double dt, double *y, double *v);
