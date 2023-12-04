#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

const int data[][50] = {
#include "data.txt"
};

int main(int argc, char* argv[])
{
  int seppos;
  unsigned long sum = 0;
  
  for(int i=1;1;i++)
  {
    if(data[0][i]==-1)
    {
      seppos = i;
      break;
    }
  }
  printf("Each card has %i winning numbers.\n",seppos-1);
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    int cardscore = 0;
    
    for(int w=1;w<seppos;w++)
    {
      for(int n=seppos+1;1;n++)
      {
        if(!data[i][n])
        {
          break;
        }
        if(data[i][w]==data[i][n])
        {
          if(cardscore)
          {
            cardscore=cardscore<<1;
          }
          else
          {
            cardscore=1;
          }
        }
      }
    }
    printf("Card %i score %i\n",data[i][0],cardscore);
    sum+=cardscore;
  }
  printf("Sum: %lu\n",sum);
  return 0;
}
