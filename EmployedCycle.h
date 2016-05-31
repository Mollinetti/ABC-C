#ifndef EMPLOYED_CYCLE_H
#define EMPLOYED_CYCLE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "MainParameters.h"
#include "Structures.h"
#include "mt19937ar.h"
#include "vectorFunc.h"

/* FUNCTION PROTOTYPES */

void employedCycle(Bee *employedBees, FoodSource *fs, int sn, double minBound[], double maxBound[]);


/* END OF FUNCTION PROTOTYPES */


//SECOND STEP: PLACE THE EMPLOYED BEES ON THEIR FOOD SOURCES 
//in this step, the bee will search for a better solution from their food sources
//via  a local neighborhood search

void employedCycle(Bee *employedBees, FoodSource *fs, int sn, double minBound[], double maxBound[])
{
     //counter
     size_t i;
     
     //random variables for the variation formula
     int j, k;
     
     for(i = 0; i < SN; i++)
     {
           //search for new food source nearby using the formula
           //vij = xij + fiij(xij - xkj)
           
           //generating a number for j (j E (1,2...D))
           j = getBoundedRandom(0, DIM - 1);
           
           //generating a number for k (K E (1,2...SN) | K != i)
           do
           {
              k = getBoundedRandom(0, SN - 1);
           }while(k == i);
           //end do while
           
           //vij = xij + fiij(xij - xkj)
           //Karaboga (2005) says that fi can assume the value [-1, 1], but also on his later papers,
           //the value of fi can also be [-a, a]
           employedBees[i].position[j] = fs[i].position[j] + genrand_real4(0,1) * (fs[i].position[j] - fs[k].position[j]);
     
           //bounding position, if it goes beyond the minimum or maximum value, assign it to the minimum or maximum value
           if(employedBees[i].position[j] < minBound[j])
           {
              employedBees[i].position[j] = minBound[j];
           }//end if
           if(employedBees[i].position[j] > maxBound[j])
           {
              employedBees[i].position[j] = maxBound[j];
           }//end if

           //assess the fitness of the new Food Source 
           //double newFit = fitnessFunction(employedBees[i].position);
           employedBees[i].violations = fitness_viga(employedBees[i].position, employedBees[i].restrictions, &employedBees[i].posFitness, employedBees[i].violations);
           
           
           // printf("GENERATED BEE %d bee: %f %f | fitness: %f  violations : %d \n",i, employedBees[i].position[0],employedBees[i].position[1],employedBees[i].posFitness, employedBees[i].violations);
             
           //if the number of violations is lower than the old one, update the 
           //position, restrictions, violations and fitness of the new food source to the scout bee, and
           //also update those values to the food Source and setting the limit counter to 0
           if(employedBees[i].violations <  fs[i].violations)
           {
              //employedBees[i].posFitness = newFit;
              memcpy(fs[i].position, employedBees[i].position, sizeof(fs[i].position));
              memcpy(fs[i].restrictions, employedBees[i].restrictions, sizeof(fs[i].restrictions));    
              //fs[i].fitness = newFit;
              fs[i].fitness = employedBees[i].posFitness;
              fs[i].violations = employedBees[i].violations;
              fs[i].limitCounter = 0;      
              
             // puts("EMPLOYED CHANGED!"); 
             // printf("%d position: %f %f | fitness: %f \n",i, fs[i].position[0],fs[i].position[1],fs[i].fitness);
             // printf("%d bee: %f %f | fitness: %f violatios : %d \n",i, employedBees[i].position[0],employedBees[i].position[1],employedBees[i].posFitness,employedBees[i].violations);
               
           }//end if
           if(employedBees[i].violations ==  fs[i].violations)
           {
                if(employedBees[i].posFitness < fs[i].fitness)
                {                                   
                    memcpy(fs[i].position, employedBees[i].position, sizeof(fs[i].position));
                    memcpy(fs[i].restrictions, employedBees[i].restrictions, sizeof(fs[i].restrictions));    
                    fs[i].fitness = employedBees[i].posFitness;
                    fs[i].violations = employedBees[i].violations;
                    fs[i].limitCounter = 0; 
                }//end if
                else
                {
                    employedBees[i].position[j] = fs[i].position[j];
                    fs[i].limitCounter++;
                }//end else
           }//end else if
           //if not, discard it by returning the modified position of the bee to what it originally was
           //and add to the limit counter of the food source
           else
           {
               // puts("NO CHANGE!"); 
                employedBees[i].position[j] = fs[i].position[j];
                fs[i].limitCounter++;
                //printf("%d bee: %f %f | fitness: %f  violations : %d \n",i, employedBees[i].position[0],employedBees[i].position[1],employedBees[i].posFitness, employedBees[i].violations);
           }//end else
     }//end for
      
     
}//end function




#endif //EMPLOYED_CYCLE
