#ifndef ROULETTE_TABLE_H
#define ROULETTE_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "MainParameters.h"
#include "Structures.h"
#include "mt19937ar.h"
#include "vectorFunc.h"

/* FUNCTION PROTOTYPES */

void initializeTable(int sn);

void updateTable(FoodSource *fs, int sn, double *probability, double *rouletteLBound, double *rouletteUBound);

double calculateTotal(FoodSource *fs, int sn);

/* END OF FUNCTION PROTOTYPES */

//probability table for selective biased roulette
//each "row" will have the upper

//probability , lower and upper bounds
  double *prob;
  double *rouletteUpperBound;
  double *rouletteLowerBound;

//function to initialize the table contents
void initializeTable(int sn)
{ 
      prob = (double*)malloc(sn * sizeof(double));
      rouletteUpperBound = (double*)malloc(sn * sizeof(double));
      rouletteLowerBound = (double*)malloc(sn * sizeof(double));
}//end function

//function that uses the roulette wheel selection to select a foodsource based on its probabilty,
//and return its index
int chooseSource(FoodSource *fs, int sn)
{
      size_t i;
      
      double r = genrand_real1();
      
      for(i = 0; i < sn; i++)
      {
         if(r >=  rouletteLowerBound[i] && r < rouletteUpperBound[i])
         {
              return i;
         }//end if
      }//end for
}


//function that calculates the probability of a food source
double calculateTotal(FoodSource *fs, int sn)
{
     //counter
     size_t i;
     //sum
     double sum = 0;
     
     for(i = 0 ; i < sn; i++)
     {
           sum += fs[i].fitness;      
     }//end for
     
     return sum;     
}//end function

//function that updates the roulette table
void updateTable(FoodSource *fs, int sn, double *probability, double *rouletteLBound, double *rouletteUBound)      
{
     //counter
     size_t i;
     
     //sum of fitness
     double total = calculateTotal(fs,SN);
     double lower = 0.0; 
  
     for(i = 0; i < SN; i++)
      {        
         probability [i] = fs[i].fitness / total;
         rouletteLBound[i] = lower; 
         rouletteUBound[i] = lower + probability[i];
         lower = rouletteUBound[i];
         //printf("prob: %f lowerBound: %f Upper Bound: %f\n",prob[i], rouletteLowerBound[i],  rouletteUpperBound[i] );
         
      }//end for
         
}//end function
      

#endif //ROULETTE_TABLE_H
