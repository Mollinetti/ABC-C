#ifndef INIT_POP_H
#define INIT_POP_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MainParameters.h"
#include "Structures.h"
#include "mt19937ar2.h"

/* FUNCTION PROTOTYPES */

void initializeSources(FoodSource **fspp, double sn, int nPar, double minBound[], double maxBound[]);

void initializeBees(Bee **employed, Bee **onlooker, Bee **scout, FoodSource *fs, int sn);

/* END OF FUNCTION PROTOTYPES */

//function to initialize the position of food sources
void initializeSources(FoodSource **fspp, double sn, int nPar, double minBound[], double maxBound[])
{
     //allocating size to a pointer fsPtr
     FoodSource *fsPtr = (FoodSource*) malloc(sn * sizeof(FoodSource));
   
     //counters
     size_t i, j;
     
     for(i = 0; i < sn; i++)
     {
           for(j = 0; j < nPar; j++)
           {
                 //using entirely random distribution
                 //fsPtr[i].position[j] = genrand_real4(minBound[j],maxBound[j]);
                 //using not entirely random distribution
                 fsPtr[i].position[j] = minBound[j] + genrand_real1() * (maxBound[j] - minBound[j]);
                 
           }//end for
           //assess fitness for the food Source
           fsPtr[i].violations = fitness_viga(fsPtr[i].position, fsPtr[i].restrictions, &fsPtr[i].fitness, &fsPtr[i].violations);
           //fsPtr[i].fitness = fitnessFunction(fsPtr[i].position);
            //set all limit counter to 0
           fsPtr[i].limitCounter = 0;
           //printf("%d position: %f %f | fitness: %f violations : %d \n",i, fsPtr[i].position[0],fsPtr[i].position[1],fsPtr[i].fitness, fsPtr[i].violations );
     }//end for
     *fspp = fsPtr;
}//end function

//function to initialize the bees
void initializeBees(Bee **employed, Bee **onlooker, Bee **scout, FoodSource *fs, int sn)
{
     //counter
     size_t i;
     
     //allocating space for the three structures
     Bee *empPtr = NULL;
     empPtr = (Bee*)malloc(INITIALEMPLOYED * sizeof(Bee)); 
    
     Bee *onlPtr = NULL;
     onlPtr = (Bee*)malloc(INITIALONLOOKER * sizeof(Bee));

     Bee *sctPtr = NULL;
     sctPtr = (Bee*)malloc(INITIALSCOUT * sizeof(Bee));

     //placing the employed bee to their respectives food source
     for(i = 0; i < sn; i++)
     {
           //assigning to the foodSource
           //position and fitness of the bee will be the same of the food source
           //copying the position of the food source
           memcpy(empPtr[i].position, fs[i].position, sizeof(empPtr[i].position));
           memcpy(empPtr[i].restrictions, fs[i].restrictions, sizeof(empPtr[i].restrictions));
           //copying the fitness of the food source
           empPtr[i].posFitness = fs[i].fitness;
           empPtr[i].violations = fs[i].violations;
           //assigning the employed bee as employed and assigning the onlookers as unemployed
           //empPtr[i].isEmployed = 1;
           //onlPtr[i].isEmployed = 0;
           
           //printf("%d bee: %f %f | fitness: %f | violations : %d \n",i, empPtr[i].position[0],empPtr[i].position[1],empPtr[i].posFitness, empPtr[i].violations);
     }//end for
      
     //assigning ptr to allocated memory
     *employed = empPtr;
     
     *onlooker = onlPtr;
     
     *scout = sctPtr;

}//end function


#endif //INIT_POP
