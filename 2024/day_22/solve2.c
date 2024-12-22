#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

unsigned long data[] = {
#include "data.txt"
};

// [-9 9] +9 [0..18] 32 4bit per siffra -> 16bitar 64kb
//        Idx   
int price[1<<(4*5)]; 
int seen[1<<(4*5)];

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

int calc(int *diffs,int diffidx)
{
  int idx = 0;
  
  //We use 4bits for each diff.
  for(int i=0;i<4;i++)
  {
    if(diffs[diffidx]<0)
    {
      return -1;
    }
    idx <<= 5;
    idx |= diffs[diffidx];
    diffidx++;
    diffidx&=0x3;
  }
  return idx;
}


int main(int argc, char* argv[])
{
  memset(price,0,sizeof(price));
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    unsigned long sn = data[i];
    unsigned long nsn;
    int diffs[4] = {-1,-1,-1,-1};
    int diffidx = 0;
    int lastd = data[i]%10;

    memset(seen,0,sizeof(seen));
    
    for(int j=0;j<2000;j++)
    {
      int newd;
      int idx;
      
      nsn = next(sn);
      newd = nsn%10;
      diffs[diffidx] = (newd-lastd)+9; // [0..18]
      diffidx++;
      diffidx&=0x3;

      idx = calc(diffs,diffidx);
      if(idx>=0 && !seen[idx])
      {
        price[idx] += newd;
        seen[idx] = 1;
      }
      lastd = newd;
      sn = nsn;
    }
  }
  {
    int big = 0;
    int im = -1;
    int jm = -1;
    int km = -1;
    int lm = -1;

    for(int i=0;i<18;i++)
    {
      int diffs[4] = {i,0,0,0};
      
        for(int j=0;j<18;j++)
        {
          diffs[1] = j;
          for(int k=0;k<18;k++)
          {
            diffs[2] = k;
            for(int l=0;l<18;l++)
            {
              int idx;
          
              diffs[3] = l;
              idx = calc(diffs,0);
              if(price[idx]>big)
              {
                big = price[idx];
                im = i;
                jm = j;
                km = k;
                lm = l;
              }
            }
          }
        }
    }
    printf("Max %i for %i %i %i %i\n",big,im-9,jm-9,km-9,lm-9);
  }
  return 0;
}
