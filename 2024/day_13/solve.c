#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int data[] = {
#include "data.txt"
};


int main(int argc, char* argv[])
{
  int i=0;
  unsigned long bestcost=(unsigned long)-1;
  int ba = 0;
  int bb = 0;
  unsigned long costsum = 0;
  
  while(data[i]>0)
  {
    bestcost=(unsigned long)-1;
    ba = 0;
    bb = 0;

    //    search(0,0,i);
    for(int a=0;a<100;a++)
    {
      for(int b=0;b<100;b++)
      {
        int atx = a*data[i] + b*data[i+2];
        int aty = a*data[i+1] + b*data[i+3];

        if((atx == data[i+4]) &&
           (aty == data[i+5]))
        {
          unsigned long cost = (3*a) + b;
          
          if(cost<bestcost)
          {
            ba = a;
            bb = b;
            bestcost = cost;
          }
        }
        if((atx > data[i+4]) ||
           (aty > data[i+5]))
        {
          break;
        }
      }
    }
    if(ba || bb)
    {
      printf("Best solution %i: %i A %i B\n",(i/6)+1,ba,bb);
      costsum +=bestcost;
    }
    else
    {
      printf("No solution %i\n",(i/6)+1);
    }
    i+=6;
  }
  printf("Cost sum: %lu\n",costsum);
  return 0;
}
