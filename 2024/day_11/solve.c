#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

unsigned long data[] = {
#include "data.txt"
};

unsigned long *last = NULL;
unsigned long *stones = NULL;
unsigned long cnt = 0;
unsigned long lcnt = 0;

int main(int argc, char* argv[])
{
  stones = malloc(sizeof(unsigned long)*(sizeof(data)/sizeof(data[0])));
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    cnt++;
    stones[i] = data[i];
  }

  for(int i=0;i<25;i++)
  {
    unsigned long idx = 0;
    
    if(last)
    {
      free(last);
    }
    last = stones;
    lcnt = cnt;
    cnt = 0;
    stones = malloc(sizeof(unsigned long)*lcnt*2);
    for(int j=0;j<lcnt;j++)
    {
      if(!last[j])
      {
        stones[idx++] = 1;
        continue;
      }
      // even number of digits
      {
        unsigned long t = last[j];
        unsigned long t1 = 0;
        unsigned long t2 = 0;
        int digits[30];
        int digitcnt = 0;

        //printf("Looking at: %lu\n",t);
        while(t)
        {
          digits[digitcnt++] = t%10;
          t/=10;
        }
        //printf("Digitcnt: %i\n",digitcnt);
        if(digitcnt&1)
        {
          stones[idx++] = 2024*last[j];
          continue;
        }
        for(int x=digitcnt-1;x>=0;x--)
        {
          
          if(x>=(digitcnt/2))
          {
            t2*=10;
            t2+=digits[x];
          }
          else
          {
            t1*=10;
            t1+=digits[x];
          }
        }
        stones[idx++] = t2;
        stones[idx++] = t1;
      }
    }
    cnt = idx;
    printf("Gen %i: %lu stones\n",i+1,cnt);
#if 0
    printf("Gen %i: ",i+1);
    for(int y=0;y<cnt;y++)
    {
      printf("%lu ",stones[y]);
    }
    printf("\n");
#endif
  }
  return 0;
}
