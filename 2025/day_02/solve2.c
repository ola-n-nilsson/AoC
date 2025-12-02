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

int helper(char* buf, int len, int slen)
{
  int rep;
  
  if(len%slen)
  {
    return 0;
  }
  // This could be a sequence
  rep = len/slen;
  for(int pos=0;pos<slen;pos++)
  {
    for(int s=1;s<rep;s++)
    {
      if(buf[(s*slen)+pos]!=buf[pos])
      {
        return 0;
      }
    }
  }
  return 1;
}

int isfake(unsigned long n)
{
  char buf[100];
  int len;
  
  snprintf(buf,sizeof(buf),"%lu",n);
  len = strlen(buf);

  for(int slen=1;slen<=len/2;slen++)
  {
    if(helper(buf,len,slen))
    {
      return 1;
    }
  }
  return 0;
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
