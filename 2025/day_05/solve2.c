#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

unsigned long data[] = {
#include "data.txt"
};

#define MIN(a,b) ( a < b ? a : b)
#define MAX(a,b) ( a > b ? a : b)

int main(int argc, char* argv[])
{
  int invpos = 0;
  unsigned long sum = 0;
  int merged = 1;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=2)
  {
    if(!data[i] && !data[i+1])
    {
      invpos=i+2;
      break;
    }
  }

  while(merged)
  {
    merged = 0;
    for(int i=0;i<(invpos);i+=2)
    {
      for(int j=0;j<(invpos);j+=2)
      {
        if(i!=j && data[i] && data[j])
        {
          if((data[i]>=data[j] && data[i]<=data[j+1]) ||
             (data[i+1]>=data[j] && data[i+1]<=data[j+1]))
          {
            merged++;
            data[i] = MIN(data[i],data[j]);
            data[i+1] = MAX(data[i+1],data[j+1]);
            data[j] = 0;
            data[j+1] = 0;
          }
        }
      }
    }
    printf("Merged: %i\n",merged);
  }

  for(int i=0;i<(invpos);i+=2)
  {
    if(data[i])
    {
      unsigned long diff;
      
      printf("Range %lu %lu ",data[i],data[i+1]);
      diff = data[i+1]-data[i]+1;
      printf("len %lu\n",diff);
      sum+=diff;
    }
  }
  
  printf("Sum: %lu\n",sum);
  return 0;
}
