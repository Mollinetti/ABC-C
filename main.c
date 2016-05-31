#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ABC.h"
#include "InitPop.h"
#include "Structures.h"
#include "MainParameters.h"
#include "EmployedCycle.h"
#include "OnlookerCycle.h"
#include "ScoutCycle.h"
#include "Finder.h"


int main()
{
  //Seed random
  srand(time(NULL));
  
  //initializing MT
  init_genrand(time(NULL));  
  //printf("\n\n%i\n\n",INITIALONLOOKER);
  //printf("\n\n%i\n\n",LIMIT);
  
  ABC(fs,employedBees,onlookerBees,scoutBees,min,max,SN,MCN,DIM,LIMIT);
 // system("PAUSE");	
  return 0;
 
 
  
}
//end main
