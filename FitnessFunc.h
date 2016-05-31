#ifndef FITNESS_FUNC_H
#define FITNESS_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "MainParameters.h"
#include "MinFunctions.h"
#include "DPVConstantes.h"
#include "DPVFitness.h"

/* Function Prototypes */

 double fitnessFunction(double *val);
 
 /* End of Function Prototypes */

//header that contains all the fitness function to test in the ABC

//arbitrary function to test
double fitnessFunction(double *val)
{
       return calcSphere(val,DIM);
       
}//end function

//constrained function



#endif //FITNESS_FUNC
