#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

int maxx;
int maxy;

char beams[256][256];

int main(int argc, char* argv[])
{
  int moved = 1;
  int beamc = 0;
  
  maxx = strlen(data[0]);
  maxy = sizeof(data)/sizeof(data[0]);

  memset(beams,0,sizeof(beams));
  
  for(int x=0;x<maxx;x++)
  {
    if(data[0][x]=='S')
    {
      beams[0][x] = 1;
      break;
    }
  }
  
  while(moved)
  {
    moved = 0;

    for(int y=0;y<maxy;y++)
    {
      for(int x=0;x<maxx;x++)
      {
        if(beams[y][x] && (y+1<maxy) && !beams[y+1][x] && data[y+1][x]=='.')
        {
          moved++;
          beams[y+1][x] = 1;
        }
        if(beams[y][x] && (y+1<maxy) && data[y+1][x]=='^')
        {
          int split = 0;
          
          if(x && !beams[y+1][x-1] && data[y+1][x-1]=='.')
          {
            moved++;
            split = 1;
            beams[y+1][x-1] = 1;
          }
          if(((x+1)<maxx) && !beams[y+1][x+1] && data[y+1][x+1]=='.')
          {
            moved++;
            split = 1;
            beams[y+1][x+1] = 1;
          }
          beamc += split;
        }
      }
    }
  }


  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      if(beams[y][x])
      {
        printf("|");
      }
      else
      {
        printf("%c",data[y][x]);
      }
    }
    printf("\n");
  }
  
  printf("Beam count: %i\n",beamc);
  
  return 0;
}
