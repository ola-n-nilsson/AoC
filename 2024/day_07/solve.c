#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

unsigned long data[] = {
#include "data.txt"
};

unsigned long calc(unsigned long* p, int op, int len)
{
  unsigned long res = p[0];

  for(int i=1;i<len;i++)
  {
    if(!(op & 1))
    {
      res+=p[i];
    }
    else
    {
      res*=p[i];
    }
    op = op>>1;
  }
  return res;
}

int main(int argc, char* argv[])
{
  int i = 0;
  int cnt = 0;
  int tcnt = 0;
  unsigned long res;
  unsigned long sum = 0;
  
  while(data[i]!=-1)
  {
    int op = 0;
    int len = 0;

    tcnt++;
    
    while(data[i+1+len]!=-1)
    {
      len++;
    }
    printf("Trying %i with len %i and result %lu\n",tcnt,len,data[i]);
    while(op<(1<<(len-1)))
    {
      res = calc(&data[i+1],op,len);
      if(res==data[i])
      {
        cnt++;
        printf("Test %i calculated!\n",tcnt);
        sum += data[i];
        break;
      }
      op++;
    }
    i+=len+2;
  }
  printf("Count: %i with sum: %lu\n",cnt,sum);
  return 0;
}
