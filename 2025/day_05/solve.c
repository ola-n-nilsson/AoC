#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

unsigned long data[] = {
#include "data.txt"
};

int main(int argc, char* argv[])
{
  int invpos = 0;
  int sum = 0;

  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=2)
  {
    if(!data[i] && !data[i+1])
    {
      invpos=i+2;
      break;
    }
  }

  for(int i=invpos;i<(sizeof(data)/sizeof(data[0]));i+=2)
  {
    printf("Checking %lu\n",data[i]);
    for(int j=0;j<invpos;j+=2)
    {
      if(data[i]>=data[j] && data[i]<=data[j+1])
      {
        //Fresh
        printf("%lu is fresh\n",data[i]);
        sum++;
        break;
      }
    }
  }
  printf("Sum: %i\n",sum);
  return 0;
}
