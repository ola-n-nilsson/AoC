#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#if 1
int time[] = {60,     80,     86,     76};
int distance[] = {601,   1163,   1559,   1300};
#else
int time[] = {7,  15,   30};
int distance[] = {9,  40,  200};
#endif

int solve(int time, int distance)
{
  int solutions = 0;
  
  for(int h=1;h<time;h++)
  {
    int speed = h;
    int rt = time - h;
    int rd = speed*rt;

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
