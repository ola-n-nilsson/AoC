#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

const char data[] = 
#include "data.txt"
;

int main(int argc, char* argv[])
{
  for(int i=0;i<((sizeof(data)/sizeof(data[0]))-14);i++)
  {
    //    printf("%c",data[i]);
    if(
       (data[i] != data[i+1]) &&
       (data[i] != data[i+2]) &&
       (data[i] != data[i+3]) &&
       (data[i] != data[i+4]) &&
       (data[i] != data[i+5]) &&
       (data[i] != data[i+6]) &&
       (data[i] != data[i+7]) &&
       (data[i] != data[i+8]) &&
       (data[i] != data[i+9]) &&
       (data[i] != data[i+10]) &&
       (data[i] != data[i+11]) &&
       (data[i] != data[i+12]) &&
       (data[i] != data[i+13]) &&

       (data[i+1] != data[i+2]) &&
       (data[i+1] != data[i+3]) &&
       (data[i+1] != data[i+4]) &&
       (data[i+1] != data[i+5]) &&
       (data[i+1] != data[i+6]) &&
       (data[i+1] != data[i+7]) &&
       (data[i+1] != data[i+8]) &&
       (data[i+1] != data[i+9]) &&
       (data[i+1] != data[i+10]) &&
       (data[i+1] != data[i+11]) &&
       (data[i+1] != data[i+12]) &&
       (data[i+1] != data[i+13]) &&

       (data[i+2] != data[i+3]) &&
       (data[i+2] != data[i+4]) &&
       (data[i+2] != data[i+5]) &&
       (data[i+2] != data[i+6]) &&
       (data[i+2] != data[i+7]) &&
       (data[i+2] != data[i+8]) &&
       (data[i+2] != data[i+9]) &&
       (data[i+2] != data[i+10]) &&
       (data[i+2] != data[i+11]) &&
       (data[i+2] != data[i+12]) &&
       (data[i+2] != data[i+13]) &&
       
       (data[i+3] != data[i+4]) &&
       (data[i+3] != data[i+5]) &&
       (data[i+3] != data[i+6]) &&
       (data[i+3] != data[i+7]) &&
       (data[i+3] != data[i+8]) &&
       (data[i+3] != data[i+9]) &&
       (data[i+3] != data[i+10]) &&
       (data[i+3] != data[i+11]) &&
       (data[i+3] != data[i+12]) &&
       (data[i+3] != data[i+13]) &&

       (data[i+4] != data[i+5]) &&
       (data[i+4] != data[i+6]) &&
       (data[i+4] != data[i+7]) &&
       (data[i+4] != data[i+8]) &&
       (data[i+4] != data[i+9]) &&
       (data[i+4] != data[i+10]) &&
       (data[i+4] != data[i+11]) &&
       (data[i+4] != data[i+12]) &&
       (data[i+4] != data[i+13]) &&

       (data[i+5] != data[i+6]) &&
       (data[i+5] != data[i+7]) &&
       (data[i+5] != data[i+8]) &&
       (data[i+5] != data[i+9]) &&
       (data[i+5] != data[i+10]) &&
       (data[i+5] != data[i+11]) &&
       (data[i+5] != data[i+12]) &&
       (data[i+5] != data[i+13]) &&

       (data[i+6] != data[i+7]) &&
       (data[i+6] != data[i+8]) &&
       (data[i+6] != data[i+9]) &&
       (data[i+6] != data[i+10]) &&
       (data[i+6] != data[i+11]) &&
       (data[i+6] != data[i+12]) &&
       (data[i+6] != data[i+13]) &&

       (data[i+7] != data[i+8]) &&
       (data[i+7] != data[i+9]) &&
       (data[i+7] != data[i+10]) &&
       (data[i+7] != data[i+11]) &&
       (data[i+7] != data[i+12]) &&
       (data[i+7] != data[i+13]) &&

       (data[i+8] != data[i+9]) &&
       (data[i+8] != data[i+10]) &&
       (data[i+8] != data[i+11]) &&
       (data[i+8] != data[i+12]) &&
       (data[i+8] != data[i+13]) &&

       (data[i+9] != data[i+10]) &&
       (data[i+9] != data[i+11]) &&
       (data[i+9] != data[i+12]) &&
       (data[i+9] != data[i+13]) &&

       (data[i+10] != data[i+11]) &&
       (data[i+10] != data[i+12]) &&
       (data[i+10] != data[i+13]) &&

       (data[i+11] != data[i+12]) &&
       (data[i+11] != data[i+13]) &&

       (data[i+12] != data[i+13]))

      {
      printf("pos: %i %c%c%c%c\n",i,data[i],data[i+1],data[i+2],data[i+3]);
      }
  }
  printf("\n");
  return 0;
}


