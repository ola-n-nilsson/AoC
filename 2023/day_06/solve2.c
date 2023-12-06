#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#if 1
unsigned long time[] = {60808676};
unsigned long distance[] = {601116315591300};
#else
unsigned long time[] = {71530};
unsigned long distance[] = {940200};
#endif

unsigned long solve(unsigned long time, unsigned long distance)
{
  unsigned long solutions = 0;
  
  for(unsigned long h=1;h<time;h++)
  {
    unsigned long speed = h;
    unsigned long rt = time - h;
    unsigned long rd = speed*rt;

    if(rd>distance)
    {
      solutions++;
    }
  }
  return solutions;
}

int main(int argc, char* argv[])
{
  unsigned long product = 1;
  
  for(int i=0;i<(sizeof(time)/sizeof(time[0]));i++)
  {
    int solutions = solve(time[i],distance[i]);
    printf("Nbr solutions for %i: %i\n",i,solutions);
    product*=solutions;
  }
  printf("Solutions: %lu\n",product);
  return 0;
}
