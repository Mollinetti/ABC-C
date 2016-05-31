#ifndef ABC_H
#define ABC_H

#include <stdio.h>
#include <stdlib.h>
#include "InitPop.h"
#include "Structures.h"
#include "MainParameters.h"
#include "EmployedCycle.h"
#include "OnlookerCycle.h"
#include "ScoutCycle.h"
#include "Finder.h"
#include "FileWriter.h"


/* FUNCTION PROTOTYPES */

void ABC(FoodSource *fs, Bee *employedBees, Bee *onlookerBees, Bee *scoutBees, double min[], 
          double max[], size_t sn, size_t maxCycle, size_t dimension, size_t limit);

/* END OF FUNCTION PROTOTYPES */

void ABC(FoodSource *fs, Bee *employedBees, Bee *onlookerBees, Bee *scoutBees, double min[], 
          double max[], size_t sn, size_t maxCycle, size_t dimension, size_t limit)
{
  //global counters
  size_t i, j;
  puts("STARTING..\n\n");  
  puts("INITIALIZING SOURCE\n\n");  
  //initializing random sources
  initializeSources(&fs,sn,dimension,min,max);
  
  puts("\n\nINITIALIZING BEES\n\n");  
  //initializing bees
  initializeBees(&employedBees,&onlookerBees,&scoutBees,fs,sn);
  
  //main cycle
  for(i = 0; i < maxCycle; i++)
  {
      //emloyed cycle
      //puts("\n\nEMPLOYED CYCLE\n\n");  
      employedCycle(employedBees,fs,INITIALEMPLOYED,min,max);
      //onlooker cycle
      //puts("\n\nONLOOKER CYCLE\n\n"); 
      
      onlookerCycle(onlookerBees,fs,INITIALONLOOKER,min,max);

      //if the food source reaches the limit, it has been abandoned, and it will
      //be generated a random position for it
     // puts("\n\nSCOUT CYCLE\n\n"); 
     
      scoutCycle(scoutBees,fs,SN,limit,limPool,LIM_POOL,min,max);
      
      //return the best of this generation
      findBest(fs,SN,i);
      
      
      
  }//end for
  writeResult(bBuf,maxCycle);
  puts("THE ALGORITHM HAS ENDED SUCCESFULLY,yay!\n\n"); 
  
  //free ptrs
  //free(fs);
  //free(employedBees);
  //free(onlookerBees);
  //free(scoutBees);
}//end function

#endif //ABC_H
