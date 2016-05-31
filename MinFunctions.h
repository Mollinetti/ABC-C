#ifndef MINIMIZING_FUNCTIONS_H
#define MINIMIZING_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double problemG1(double *arr);

//function of problem G1
double problemG1(double *arr)
{
           
       return (arr[0] * (double)sin((4* arr[0]))) + (1.1 * arr[1] * (double)sin((2 * arr[1])));   
}
//end function

#endif //MINIMIZING_FUNCTIONS_H
