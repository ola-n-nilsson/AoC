#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

const int crabpos[] =
{
#include "data.c"
};

int main(int argc,char* argv[])
{
  int sums[1950];
  int steps[1950];
  int minpos_fuel = INT_MAX;
  int minpos = 0;
  
  memset(sums,0,sizeof(sums));

  steps[0] = 0;
  for(int i=1;i<sizeof(steps)/sizeof(steps[0]);i++)
  {
    steps[i] = steps[i-1] + i;
  }

  for(int pos=0;pos<(sizeof(sums)/sizeof(sums[0]));pos++)
  {
    for(int i=0;i<sizeof(crabpos)/sizeof(crabpos[0]);i++)
      sums[pos] += steps[abs(crabpos[i]-pos)];
    if(sums[pos] < minpos_fuel)
    {
      minpos_fuel = sums[pos];
      minpos = pos;
    }
  }

  printf("Pos: %i fuel: %i\n",minpos,minpos_fuel);
  
  return 0;
}
