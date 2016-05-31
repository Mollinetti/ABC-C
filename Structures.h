#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include "MainParameters.h"
#include "WBDConstantes.h"

typedef struct
{
        //violations counter
        size_t violations;
        //limit counter, if the counter surpasses the 
        //LIMIT variable, it means that the foodsource has been depleted
        size_t limitCounter;
        double fitness;
        double position[DIM];
        //restrictions
        double restrictions[NUM_RESTRICOES]; 
        //probability of a food source
        double probability; 
       
}FoodSource;

typedef struct
{
        //violations counter
        size_t violations;
        //position the bee is currently at
        double position[DIM]; 
        //fitness of the current position
        double posFitness;
         //boolean to check if a bee is employed or unemployed 
        //size_t isEmployed;
         //restrictions
        double restrictions[NUM_RESTRICOES];
       
}Bee;


//FoodSources
FoodSource *fs;

//The three kinds of bee

Bee *employedBees;

Bee *onlookerBees;

Bee *scoutBees;

//buffer of the best sources

FoodSource *bBuf;

#endif //STRUCTURES
