#ifndef MAIN_PARAMETERS_H
#define MAIN_PARAMETERS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "WBDConstantes.h"
#include "WBDFitness.h"

//----------------- ABC RELATED CONSTANTS-------------------------------//

//problem dimension (number of optimization parameters)
#define DIM              4

//maximum cycle number
#define MCN              3000

//number of initial food sources
#define SN               40 

//number of initial onlooker BEES
#define INITIALONLOOKER  (int)SN/2

//number of initial employed BEES
#define INITIALEMPLOYED  (int)SN

//number of initial scout BEES
#define INITIALSCOUT     1

//limit parameter
#define LIMIT            (int)SN * DIM


//----------------- TOURNAMENT RELATED CONSTANTS -----------------//
//size of tournament population
#define TN_POP           2

//tournament pool size
#define TN_POOL          (int)SN

//limit pool maximum size
#define LIM_POOL         (int)SN


//----------------- GLOBAL VARIABLES -----------------//

//boundaries, or also called the search space 
double min[] = {ESPACO_MIN_H , ESPACO_MIN_L, ESPACO_MIN_T, ESPACO_MIN_B};
double max[] = {ESPACO_MAX_H, ESPACO_MAX_L, ESPACO_MAX_T, ESPACO_MAX_B};

//tournament pool
int *tnPool;

//exhausted sources pool
int *limPool;


#endif //MAIN_PARAMETERS
