#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

unsigned long data[] = {
#include "data.txt"
};

int main(int argc, char* argv[])
{
  int len = 0;
  unsigned long sum = 0;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    if(!data[i])
    {
      len = i+1;
      break;
    }
  }

  for(int i=0;i<(len-1);i++)
  {
    printf("%c (%lu) ",(int)data[i+(4*len)],data[i+(4*len)]);
    if(data[i+(4*len)]=='+')
    {
      unsigned long nbr = data[i] + data[i+len] + data[i+(2*len)] + data[i+(3*len)];
      printf("Summed to: %lu\n",nbr);
      sum+=nbr;
    }
    else
    {
      unsigned long nbr = data[i] * data[i+len] * data[i+(2*len)] * data[i+(3*len)];
      printf("Mult to: %lu\n",nbr);
      sum+=nbr;
    }
  }
  printf("Sum: %lu\n",sum);
  return 0;
}
