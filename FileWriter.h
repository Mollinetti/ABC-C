#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include <stdio.h>
#include <stdlib.h>


/* FUNCTION PROTOTYPES */

void writeResult(FoodSource *buffer, size_t size);

/* END OF FUNCTION PROTOTYPES */

//file writer part

//function that generates a .dat file called results that includes the results of the test
void writeResult(FoodSource *buffer, size_t size)
{
    //counter
    size_t i;
    //open file in order to write 
    FILE* file = fopen("C:/Users/Mollinetti/Dropbox/result.dat","w");
    if(file == NULL)
    {
        puts("could not open the file.");    
    }//end if
    else
    {
        for(i = 0; i < size; i++)
        {
          fprintf(file, "%-12f %-12f %-12f %-12f %-12f %-12f %-12f %-12f %-12f %-12f %-12f %-12f %-12d\n" ,
          buffer[i].position[0], buffer[i].position[1], buffer[i].position[2], buffer[i].position[3],
          buffer[i].restrictions[0], buffer[i].restrictions[1], buffer[i].restrictions[2], buffer[i].restrictions[3],
           buffer[i].restrictions[4],  buffer[i].restrictions[5],  buffer[i].restrictions[6],
           buffer[i].fitness, buffer[i].violations); 
        }//end for
    }//end else
    fclose(file);
}//end function



#endif //FILE_WRITER_H
