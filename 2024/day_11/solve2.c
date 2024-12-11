#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

unsigned long data[] = {
#include "data.txt"
};

unsigned long seen[20000];
unsigned long cnt[20000];
unsigned long lcnt[20000];
int sidx = 0;

int insert(unsigned long x)
{
  for(int i=0;i<sidx;i++)
  {
    if(seen[i]==x)
    {
      return i;
    }
  }
  seen[sidx++] = x;
  if(sidx>=(sizeof(seen)/sizeof(seen[0])))
  {
    printf("More than %i\n",sidx);
    exit(-1);
  }
  return sidx-1;
}

int main(int argc, char* argv[])
{
  memset(cnt,0,sizeof(cnt));
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    int idx = insert(data[i]);

    cnt[idx]++;
  }

  for(int i=0;i<75;i++)
  {
    int lsidx = sidx;
    
    memcpy(lcnt,cnt,sizeof(cnt));
    memset(cnt,0,sizeof(cnt));

    for(int j=0;j<lsidx;j++)
    {
      unsigned long stone = seen[j];
    
      if(!stone)
      {
        int oneidx = insert(1);
        cnt[oneidx] += lcnt[j];
        continue;
      }
      // even number of digits
      {
        unsigned long t = stone;
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
          unsigned long nstone = 2024*stone;
          int nidx = insert(nstone);

          cnt[nidx]+=lcnt[j];
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
        {
          int t1idx = insert(t1);
          int t2idx = insert(t2);

          cnt[t1idx]+=lcnt[j];
          cnt[t2idx]+=lcnt[j];
        }
      }
    }
    {
      unsigned long scnt = 0;

      for(int x=0;x<sidx;x++)
      {
        scnt+=cnt[x];
      }

      printf("Gen %i: count %lu\n",i+1,scnt);
    }
  }
  return 0;
}
