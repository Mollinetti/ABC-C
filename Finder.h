#ifndef FILEFINDER_H
#define FILEFINDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "MainParameters.h"
#include "Structures.h"

/* FUNCTION PROTOTYPES */

void *findBest(FoodSource *fs, size_t sn, size_t it);

/* END OF FUNCTION PROTOTYPES */


//function to find the best food source of each cycle
//every iteration will increase the size of the buffer
void *findBest(FoodSource *fs, size_t sn, size_t it)
{
    bBuf = realloc(bBuf, (it + 1) * sizeof(FoodSource));       
    //counter
    size_t i;
    FoodSource *best = fs;
    for(i = 0; i < sn; i++)
    {
          //if the solution has less violations than the best, assign it to be the best 
          if(fs[i].violations < best->violations)
          {    
             best = &fs[i];
          }//end if
          //wheres its number of violations is the same, evaluate the solution by means of choosing the one that has the lowest fitness
          else if (fs[i].violations == best->violations)
          {
               if(fs[i].fitness < best->fitness)
               {
                 best = &fs[i];
               }//end if
          }//end else if
    }//end for
    
    //printf("fit %f\n",best->fitness);
    //copy value of the best to the buffer 
    memcpy(&bBuf[it], best, sizeof(bBuf[it]));
    //printf("Best Source -> fitness:%f | pos1:%f  pos2:%f| vio: %d \n", best->fitness, best->position[0], best->position[1], best->violations);
   // printf("bBuf fit %f\n",bBuf[it].fitness);
}//end function


#endif //FILEFINDER_H
