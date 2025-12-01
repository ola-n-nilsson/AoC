#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct move_t
{
  char dir;
  int len;
} move_t;

move_t data[] = {
#include "data.txt"
};

int main(int argc, char* argv[])
{
  int place = 50;
  int zeros = 0;
  int dir = 0;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    if(data[i].dir=='L')
    {
      dir = -1;
    }
    else
    {
      dir = 1;
    }
    for(int j=0;j<data[i].len;j++)
    {
      place += dir;
      place %= 100;
      if(!place)
      {
        zeros++;
      }
    }
  }
  printf("Pass: %i\n",zeros);
  return 0;
}
