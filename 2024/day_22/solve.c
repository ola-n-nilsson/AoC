#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

unsigned long data[] = {
#include "data.txt"
};

unsigned long next(unsigned long snin)
{
  unsigned long step;

  step = snin*64;
  snin = snin ^ step;
  snin = snin % 16777216;
  step = snin/32;
  snin = snin ^ step;
  snin = snin % 16777216;
  step = snin*2048;
  snin = snin ^ step;
  snin = snin % 16777216;
  
  return snin;
}

int main(int argc, char* argv[])
{
  unsigned long sum = 0;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    unsigned long sn = data[i];
    for(int j=0;j<2000;j++)
    {
      sn = next(sn);
    }
    printf("%lu: %lu\n",data[i],sn);
    sum += sn;
  }
  printf("Sum: %lu\n",sum);
  return 0;
}
