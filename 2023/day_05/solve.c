#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "data.h"

unsigned long convert(unsigned long seed)
{
  //  printf("Before: %lu\n",seed);
  for(int i=0;i<(sizeof(maps)/sizeof(maps[0]));i++)
  {
    for(int j=0;j<maps[i].len;j+=3)
    {
      if((seed>=maps[i].map[j+1]) && (seed<(maps[i].map[j+1] + maps[i].map[j+2])))
      {
        unsigned long offset = seed - maps[i].map[j+1];
        seed = maps[i].map[j] + offset;
        //printf("Converted to: %lu\n",seed);
        break;
      }
    }
  }
  //printf("Result: %lu\n",seed);
  return seed;
}

int main(int argc, char* argv[])
{
  unsigned long  min_loc = (unsigned long)-1;

  for(int i=0;i<(sizeof(seeds)/sizeof(seeds[0]));i++)
  {
    unsigned long converted = convert(seeds[i]);
    printf("seed %i: %lu\n",i,seeds[i]);
    printf("converts to: %lu\n",converted);
    if(converted<min_loc)
    {
      min_loc = converted;
    }
  }
  printf("Min loc: %lu\n",min_loc);
  return 0;
}
