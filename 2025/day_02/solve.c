#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct range_t {
  unsigned long start;
  unsigned long end;
} range_t;

range_t data[] = {
#include "data.txt"
};

int isfake(unsigned long n)
{
  char buf[100];
  int len;
  char remember;
  unsigned long one;
  unsigned long two;
  
  snprintf(buf,sizeof(buf),"%lu",n);
  len = strlen(buf);
  if(len&1)
  {
    return 0;
  }
  remember = buf[len/2];
  buf[len/2] = '\0';
  sscanf(buf,"%lu",&one);    
  buf[len/2] = remember;
  sscanf(&buf[len/2],"%lu",&two);
  return one==two;
}

int main(int argc, char* argv[])
{
  unsigned long sum = 0;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    printf("Looking at range %lu-%lu\n",data[i].start,data[i].end);
    for(unsigned long j=data[i].start;j<=data[i].end;j++)
    {
      if(isfake(j))
      {
        printf("Is fake: %lu\n",j);
        sum += j;
      }
    }
  }
  printf("Sum: %lu\n",sum);
  return 0;
}
