#ifndef SCOUT_CYCLE_H
#define SCOUT_CYCLE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "MainParameters.h"
#include "Structures.h"
#include "mt19937ar.h"
#include "vectorFunc.h"

/* Function Prototypes */

 void ScoutCycle(Bee *scoutBee, FoodSource *fs, int sn, int limit, int *pool, size_t poolSize, double min[], double max[]);

 void scoutSource(Bee *scoutBee, FoodSource *fs, int sn, double min[], double max[]);
 
 double findMaxPosition(FoodSource *fs, int j, int sn);
 
 double findMinPosition(FoodSource *fs, int j, int sn);
 
 int buildLimitPool(int **pool, FoodSource *fs, size_t limit);
 
 int getLimit(int *pool, int *size);
/* End of Function Prototypes */
 

//simulation of the whole scout cycle
void scoutCycle(Bee *scoutBee, FoodSource *fs, int sn, int limit, int *pool, size_t poolSize, double min[], double max[])
{
     //build pool
     int size = buildLimitPool(&pool, fs, limit);
     
     if(size > 0)
     {
         //select random source from pool
         int index = getLimit(pool,size);
             
         //employ the scout procedure to the chosen index representing the exhausted source
         scoutSource(scoutBee, &fs[index], sn, min,max);
     }//end if     
     //free the pool ptr
     free(pool);
     
}//end function

void scoutSource(Bee *scoutBee, FoodSource *fs, int sn, double min[], double max[])
{
     //copy the value of the food source to the bee
     memcpy(scoutBee->position, fs->position, sizeof(scoutBee->position));
     scoutBee->posFitness = fs->fitness;
     
     //random number for j
     int j = getBoundedRandom(0, DIM - 1);
     
     //assigning the new updated random position
     scoutBee->position[j] = min[j] + genrand_real1() * (max[j] - min[j]);
     
      //bounding position, if it goes beyond the minimum or maximum value, assign it to the minimum or maximum value
       if( scoutBee->position[j] < min[j])
       {
           scoutBee->position[j] = min[j];
       }//end if
       else if( scoutBee->position[j] > max[j])
       {
           scoutBee->position[j] = max[j];
       }//end if
     
     //assess the fitness of the food source found by the scout bee
     //double newFit = fitnessFunction(scoutBee->position);
      scoutBee->violations = fitness_viga(scoutBee->position,scoutBee->restrictions, &scoutBee->posFitness, scoutBee->violations);
     
      //if the number of violations is lower than the old one, update the 
       //position, restrictions, violations and fitness of the new food source to the scout bee, and
       //also update those values to the food Source
       if(scoutBee->violations < fs->violations)
       {
          //scoutBee->posFitness = newFit;
          memcpy(fs->position, scoutBee->position, sizeof(fs->position));
          memcpy(fs->restrictions, scoutBee->restrictions, sizeof(fs->restrictions));    
          fs->fitness = scoutBee->posFitness; 
          fs->violations = scoutBee->violations;      
          fs->limitCounter = 0;
          //puts("SCOUT CHANGED!"); 
          //printf("position: %f %f | fitness: %f violations %d \n", fs->position[0],fs->position[1],fs->fitness, fs->violations);
          //printf("bee: %f %f | fitness: %f \n",scoutBee->position[0],scoutBee->position[1],scoutBee->posFitness);
          //puts("check"); 
       }//end if
       //if the number of violations is the same, evaluate the new value by the fitness value,
       //if the new value has a lower fitness than the old, exchange it
       if(scoutBee->violations == fs->violations)
       {
            if(scoutBee->posFitness < fs->fitness)
            {
              memcpy(fs->position, scoutBee->position, sizeof(fs->position));
              memcpy(fs->restrictions, scoutBee->restrictions, sizeof(fs->restrictions));    
              fs->fitness = scoutBee->posFitness; 
              fs->violations = scoutBee->violations;      
              fs->limitCounter = 0;  
              //puts("SCOUT CHANGED!"); 
              //printf("position: %f %f | fitness: %f violations %d \n", fs->position[0],fs->position[1],fs->fitness, fs->violations);
              //printf("bee: %f %f | fitness: %f \n",scoutBee->position[0],scoutBee->position[1],scoutBee->posFitness);
              //puts("check");                     
            }//end if
            else
            {
              //puts("SCOUT NOT CHANGED!");  
              scoutBee->position[j] = fs->position[j];
              fs->limitCounter++;
            }//end else
       }//end else if
       //if not, discard it by returning the modified position of the bee to what it originally was
       //and add to the limit counter of the food source
       else
       {
           // puts("NO CHANGE!"); 
            scoutBee->position[j] = fs->position[j];
            fs->limitCounter++;
           // printf("bee: %f %f | fitness: %f \n",scoutBee->position[0],scoutBee->position[1],scoutBee->posFitness);
       }//end else
 
}//end function


//function to build a pool containing all the indexes of the sources that are considered exhausted
//since the pool is dinamycally constructed, it will return it's size
int buildLimitPool(int **pool, FoodSource *fs, size_t limit)
{
     //counter
     size_t i;
     //pool counter
     size_t pCounter = 1;
     //flag telling that there is a limit
     size_t lFlag = 0;  
     //pointer to pool, firstly, allocate to size 1
     int *poolPtr =(int*)malloc(pCounter * sizeof(int));
       
     for( i = 0; i < SN; i++ )
     {
          if(fs[i].limitCounter >= limit)
          {  
             lFlag++;
             poolPtr[pCounter - 1] = i;
             pCounter++;         
             poolPtr = (int*)realloc(poolPtr, pCounter * sizeof(int));
             //printf("\n = %d\n", pCounter);
          }//end if 
     }//end for
     
     //assigning ptr of pool to the poolPtr
     *pool = poolPtr;  
   
     //return the size of the pool
     if(pCounter <= 1 && lFlag == 0)
     {
       return 0;
     }//end if
     else if(pCounter <= 1 && lFlag > 0)
     {
       return 1;
     }//end if
     else
     {
       return pCounter - 1;
     }
}//end function

//function that returns a random value from the limit pool
int getLimit(int *pool, int *size)
{
    int val = size;
  
    int i = (int)genrand_real4(0,val);
     
     
    int num = pool[i];
    //printf("\nnum = %d\n", num); 
    
    //reducing the pool
    pool[i] = pool[val - 1];
    pool[val - 1] = num;
    
    
    pool = realloc(pool, (val - 1) * sizeof(int));
    size--;
    return num;
}//end function




//function that finds the maximum value of a position among the food sources
double findMaxPosition(FoodSource *fs, int j, int sn)
{
       //counter
       size_t i;
       
       double biggest = fs[0].position[j];
       
       for(i = 0; i < sn; i++)
       {
         if(fs[i].position[j] > biggest)
         {
            biggest = fs[i].position[j];
         }//end if
       }//end for  
       
       return biggest;           
}//end function


//function that finds the minimum value of a position among the food sources
double findMinPosition(FoodSource *fs, int j, int sn)
{
       //counter
       size_t i;
       
       double smallest = fs[0].position[j];
       
       for(i = 0; i < sn; i++)
       {
         if(fs[i].position[j] < smallest)
         {
            smallest = fs[i].position[j];
         }//end if
       }//end for  
       
       return smallest;           
}//end function




#endif // SCOUT_CYCLE_H
