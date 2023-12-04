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
  unsigned long cards[500];

  memset(cards,0,sizeof(cards));
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    cards[i] = 1;
  }
  
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
    int matches = 0;
    
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
          matches+=1;
        }
      }
    }
    printf("Card %i matches %i and we have %lu copies\n",data[i][0],matches,cards[i]);
    for(int j=i+1;j<=i+matches;j++)
    {
      if(cards[j])
      {
        cards[j] += cards[i];
      }
    }
  }

  {
    unsigned long sum  = 0;
    for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
    {
      printf("We have %lu of card %i\n",cards[i],i+1);
      sum += cards[i];
    }
    printf("Sum: %lu\n",sum);
  }

  return 0;
}
