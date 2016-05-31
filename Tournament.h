#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "MainParameters.h"
#include "Structures.h"
#include "mt19937ar.h"
#include "vectorFunc.h"

/* FUNCTION PROTOTYPES */

int tournament(FoodSource *fs, size_t tnPopSize);

void fillPool(int **pool, FoodSource *fs,  size_t tnPopSize, size_t poolSize);

int getPool(int *pool, size_t poolSize);

/* END OF FUNCTION PROTOTYPES */


//tournament function that pits k number of individuals against each other
//and chooses the most fit individual to be part of a pool
//repeated instances of an individual can be part of that pool

int tournament(FoodSource *fs, size_t tnPopSize)
{
    //counter 
    size_t i;
    //random index
    size_t index;
    //best food source
    FoodSource *Best = NULL;
    //best index
    size_t bIndex;
    //initialize unique random number pool
    getUniqueRandom(SN);
    
    for(i = 0; i < tnPopSize; i++)
    {
      //getting a unique random number for index    
      index = getUniqueRandom(-1);
      
      if(Best == NULL || Best->violations > fs[index].violations)
      {
        Best = &fs[index];
        bIndex = index;
      }//end if
      
      else if(Best == NULL || Best->violations == fs[index].violations)
      {
           if(Best->fitness > fs[index].fitness)
           {
              Best = &fs[index];
              bIndex = index;
           }//end if
      }//end else if      
    }//end for
    
    return bIndex;
}//end function 

//function to fill the pool containing the winners of the tournament
//firstly, the space for the pool is allocated, and tournaments are carried n times
//until it fills the pool entirely
//the pool will contain the index of which food source will be chosen by the onlookers
void fillPool(int **pool, FoodSource *fs,  size_t tnPopSize, size_t poolSize)
{
     //allocate memory to pool
     int *poolPtr = (int*) malloc(poolSize * sizeof(int));
     if(*poolPtr == NULL)
     {
        puts("MEMORY FAULT, CANNOT ALLOCATE FURTHER");
     }
     //counter
     size_t i;
     
     for(i = 0; i < poolSize; i++)
     {
           poolPtr[i] = tournament(fs, tnPopSize);
     }//end for
     
     *pool = poolPtr;
}//end function

//function to return an individual from the pool
int getPool(int *pool, size_t poolSize)
{
    //random integer
    int i = (int)genrand_real4(0, poolSize - 1);
    
    return pool[i];
    
}//end function


#endif //TOURNAMENT_H
