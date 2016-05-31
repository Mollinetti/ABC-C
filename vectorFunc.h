#ifndef VECTOR_FUNC_H
#define VECTOR_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define ERR_NO_NUM -1
#define ERR_NO_MEM -2

//PROTOTYPES

 //method to find index of a vector by a value
 int findIndexByValue(double vec[], double value, int length);
 
 //method for extracting the sum of a vector
 double vecSum(const double *vec, size_t vecSize);
 
 //method to extract the minimum value from a vector
 double extractMin(const double *vec, size_t length);
 
 //method to traverse a vector and print it
 void traverseVec(const double vec[], size_t length);
 
 //method to extract the maximum value from a vector
 double extractMax(const double *vec, size_t length);
 
 //method to check if vector contains given value
 int isInVector(void *vector[], size_t length, void *value);
 
 //method to generate a bounded random number
 unsigned int getBoundedRandom(unsigned int min, unsigned int max);

//END OF PROTOTYPES

 //method to extract the minimum value from a vector
double extractMin(const double *vec, size_t length)
 {
       //counter
       int i;
       //smallest variable
       double smallest = vec[0];
       
       for(i = 0 ; i < length; i++)
       {
         if(vec[i] < smallest)
         {
             smallest = vec[i];
         }//end if
       }//end for
       return smallest;
 }//end method
 
  //method to extract the maximum value from a vector
double extractMax(const double *vec, size_t length)
 {
       //counter
       int i;
       //smallest variable
       double biggest = vec[0];
       
       for(i = 0 ; i < length; i++)
       {
         if(vec[i] > biggest)
         {
             biggest = vec[i];
         }//end if
       }//end for
       return biggest;
 }//end method
 
  //method for extracting the sum of a vector
double vecSum(const double *vec, size_t vecSize)
 { 
       //sum variable
       double sum = 0;
       //counter
       int i;
 
       for(i = 0; i < vecSize; i++)
       {
         sum = sum + vec[i];    
       }//end for
       
       return (sum);
 }//end method
 
 
 //method to traverse a vector and print it
 void traverseVec(const double vec[], size_t length)
 {
       //counter
       int i;
       for(i = 0; i < length; i++)
       {
         printf("%i : %f \n",i,vec[i]);   
       }//end for
 }//end method
 
  
//method to check if vector contains given value
int isInVector(void *vector[], size_t length, void *value)
{
    //if value is in vector return 1, else return 0
    //counter
    int i;
    
    for(i = 0; i < length; i++)
    {
          if(vector[i] == value)
          {
            return 1;
          }//end if
    }//end for
    
    return 0;
}//end method


//method to find index of a vector by a value
int findIndexByValue(double vec[], double value, int length)
{
    //counter
    size_t i;
    
    for(i = 0 ; i < length; i++)
    {
      if(vec[i] == value)
      {
          return i;
      }//end if
    }//end for
    
    //case it does not find
    return -1;
}//end method

//method to generate a bounded random number
unsigned int getBoundedRandom(unsigned int min, unsigned int max)
{
       double scaled = (double)rand()/RAND_MAX;

       return (max - min +1)*scaled + min;
}
//end method


//shuffling algorithm to get a number from a pool and then decrease it in order to avoid getting the same number
//positive numbers will generate a new list
//negative numbers will make it sort again
int getUniqueRandom (int size) {
    int i, n;
    static int numNums = 0;
    static int *numArr = NULL;

    // Initialize with a specific size.

    if (size >= 0) {
        if (numArr != NULL)
            free (numArr);
            //end if
        if ((numArr = malloc (sizeof(int) * size)) == NULL)
            return ERR_NO_MEM;
            //end if
        for (i = 0; i  < size; i++)
            numArr[i] = i;
        //end for    
        numNums = size;
        return size;
    }

    // Error if no numbers left in pool.

    if (numNums == 0)
       return ERR_NO_NUM;

    // Get random number from pool and remove it (rnd in this
    //   case returns a number between 0 and numNums-1 inclusive).

    n = rand() % numNums;
    i = numArr[n];
    numArr[n] = numArr[numNums-1];
    numNums--;
    if (numNums == 0) {
        free (numArr);
        numArr = 0;
    }//end if

    return i;
}
//end function


#endif     // VECTOR_FUNC_H

