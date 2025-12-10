#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#if 0
#if 0
char* gdata[] = {
#include "data3a.txt"
};
int mdata[] = {
#include "data3b.txt"
};
#else
char* gdata[] = {
#include "data2a.txt"
};
int mdata[] = {
#include "data2b.txt"
};
#endif
#else
char* gdata[] = {
#include "dataa.txt"
};
int mdata[] = {
#include "datab.txt"
};
#endif

unsigned int buttons[32];
unsigned int bidx = 0;

int main(int argc, char* argv[])
{
  int* lstart = &mdata[0];
  unsigned int pows[32];
  unsigned int masks[32];
  unsigned int pow = 1;
  unsigned int mask = 1;
  int sum = 0;
  
  for(int i=0;i<32;i++)
  {
    pows[i] = pow;
    masks[i] = mask;
    pow*=2;
    mask*=2;
    mask++;
  }
  
  for(int i=0;i<(sizeof(gdata)/sizeof(gdata[0]));i++)
  {
    unsigned int goal = 0;
    bidx = 0;
    
    for(int j=0;j<strlen(gdata[i]);j++)
    {
      if(gdata[i][j]=='#')
      {
        goal+=pows[j];
      }
    }
    while(*lstart!=-2)
    {
      buttons[bidx] = 0;
      while(*lstart!=-1)
      {
        buttons[bidx] += pows[*lstart];
        lstart++;
      }
      bidx++;
      lstart++;
    }
    while(*lstart!=-3)
    {
      lstart++;
    }    
    lstart++;
    // We have goal and buttons
    printf("Reach %04X\n",goal);
    for(int i=0;i<bidx;i++)
    {
      printf("Button %i: %04X\n",i,buttons[i]);
    }

    {
      int min = 32;
      mask = masks[strlen(gdata[i])-1];

      for(int j=1;j<=masks[bidx-1];j++)
      {
        //printf("Searching: %04X\n",j);
        if(__builtin_popcount(j) < min)
        {
          int bit=0;
          int val = 0;
          int pressed = j;
          
          while(pressed)
          {
            if(pressed&1)
            {
              //printf("Xoring in %04X\n",buttons[bit]);
              val ^= buttons[bit];
            }
            pressed = pressed>>1;
            bit++;
          }

          //printf("Val: %04X Mask: %04X Masked: %04X\n",val,mask,val & mask);
          
          if((val & mask) == goal)
          {
            min = __builtin_popcount(j);
          }
        }
      }
      printf("Has min: %i\n",min);
      sum+=min;

    }
  }
  printf("Sum: %i\n",sum);
  return 0;
}


// 1237 is too high
