#ifndef ONLOOKER_CYCLE_H
#define ONLOOKER_CYCLE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "MainParameters.h"
#include "Structures.h"
#include "mt19937ar.h"
#include "vectorFunc.h"
#include "Tournament.h"


/* FUNCTION PROTOTYPES */

int chooseSource(FoodSource *fs, int sn);

void onlookerCycle(Bee *onlookerBees, FoodSource *fs, int sn, double minBound[], double maxBound[]);

/* END OF FUNCTION PROTOTYPES */

//onlooker cycle, where the onlooker bees will choose a foodsource to try to 
//improve it This choice is based on the probability of each food source fitness.




//function that simulates the onlooker bees cycle,
//the bee will choose based on a biased roulette process, the higher the probability
// of a food source, the higher the likelihood of the bee chosing that food source is.
void onlookerCycle(Bee *onlookerBees, FoodSource *fs, int sn, double minBound[], double maxBound[])
{
     //counter
     size_t i;
     
     //random variables
     int j, k;
     
     //index
     int index;
     
     //creating the tournament pool
     fillPool(&tnPool, fs, TN_POP, TN_POOL);

     for(i = 0; i < sn; i++)
     {
           //get the chosen source
           index = getPool(tnPool, TN_POOL);
           //puts("escolheu");
           //printf("source %d chosen\n",index);
            
           //improve the food source denoted by the index
           //vij = xij + fiij(xij - xkj)
           
           //generating a number for j (j E (1,2...D))
           j = (int)genrand_real4(0, DIM);
          
           //generating a number for k (K E (1,2...SN) | K != i)
           do
           {
              k = (int)genrand_real4(0, sn);
           }while(k == index);
           //end do while
           //copy value of the position of the food source to the position of the onlooker bee
           memcpy(&onlookerBees[i].position, &fs[index].position , sizeof(onlookerBees[i].position)); 
           
           //vij = xij + fiij(xij - xkj)
           onlookerBees[i].position[j] = fs[index].position[j] + genrand_real4(-1,1) * (fs[index].position[j] - fs[k].position[j]);
           
           //bounding position, if it goes beyond the minimum or maximum value, assign it to the minimum or maximum value
           if(onlookerBees[i].position[j] < minBound[j])
           {
              onlookerBees[i].position[j] = minBound[j];
           }//end if
           if(onlookerBees[i].position[j] > maxBound[j])
           {
              onlookerBees[i].position[j] = maxBound[j];
           }//end if
           
           
           
           //assess the fitness of the new Food Source
           //double newFit = fitnessFunction(onlookerBees[i].position);
           onlookerBees[i].violations = fitness_viga(onlookerBees[i].position, onlookerBees[i].restrictions, &onlookerBees[i].posFitness, onlookerBees[i].violations);  
          // printf("GENERATED ONLOOKER %d bee: %f %f | fitness: %f  violations : %d \n",i, onlookerBees[i].position[0],onlookerBees[i].position[1],onlookerBees[i].posFitness, onlookerBees[i].violations);
          //if the number of violations is lower than the old one, update the 
         //position, restrictions, violations and fitness of the new food source to the scout bee, and
         //also update those values to the food Source
           if(onlookerBees[i].violations < fs[index].violations)
           {
              //onlookerBees[i].posFitness = newFit;
              memcpy(fs[index].position, onlookerBees[i].position, sizeof(fs[index].position));  
              //fs[index].fitness = newFit;
              fs[index].limitCounter = 0;
              memcpy(fs[index].restrictions,  onlookerBees[i].restrictions, sizeof(fs[index].restrictions));    
              fs[index].fitness =  onlookerBees[i].posFitness;
              fs[index].violations =  onlookerBees[i].violations;     
              //puts("ONLOOKER CHANGED!"); 
             // printf("%d position: %f %f | fitness: %f violations %d \n",index, fs[index].position[0],fs[index].position[1],fs[index].fitness, fs[index].violations);
             //printf("%d bee: %f %f | fitness: %f violations: %d \n",index, onlookerBees[i].position[0],onlookerBees[i].position[1],onlookerBees[i].posFitness, onlookerBees[i].violations);    
            // puts("check");   
           }//end if
           //if the number of violations is the same, evaluate the new value by the fitness value,
           //if the new value has a lower fitness than the old, exchange it
           if(onlookerBees[i].violations == fs[index].violations)
           {
                if(onlookerBees[i].posFitness < fs[index].fitness)
                {
                    //onlookerBees[i].posFitness = newFit;
                    memcpy(fs[index].position, onlookerBees[i].position, sizeof(fs[index].position));  
                    //fs[index].fitness = newFit;
                    fs[index].limitCounter = 0;
                    memcpy(fs[index].restrictions,  onlookerBees[i].restrictions, sizeof(fs[index].restrictions));    
                    fs[index].fitness =  onlookerBees[i].posFitness;
                    fs[index].violations =  onlookerBees[i].violations;   
                }//end if
                else
                {
                    onlookerBees[i].position[j] = fs[index].position[j];
                    fs[index].limitCounter++;
                }//end else
           }//end else if
           //if not, discard it by returning the modified position of the bee to what it originally was
           //and add to the limit counter of the food source
           else
           {
                onlookerBees[i].position[j] = fs[index].position[j];
                fs[index].limitCounter++;
               // puts("NO CHANGE!"); 
               // printf("%d bee: %f %f | fitness: %f \n",index, onlookerBees[index].position[0],onlookerBees[index].position[1],onlookerBees[index].posFitness);
           }//end else
           
     }//end for
     
     //freeing the pool
     free(tnPool);
}//end function



#endif // ONLOOKER_CYCLE_H
