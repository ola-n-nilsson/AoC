#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int maxx;
int maxy;

char* data[] = {
#include "data2.txt"
};

int main(int argc, char* argv[])
{
  int sum = 0;
  
  maxy = sizeof(data)/sizeof(data[0]);
  maxx = strlen(data[0]);

  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {

      if(data[y][x]=='@')
      {
        int adj = 0;
        
        // Above
        if(y && data[y-1][x]=='@')
        {
          adj++;
        }
        if(y && x && data[y-1][x-1]=='@')
        {
          adj++;
        }
        if(y && ((x+1)<maxx) && data[y-1][x+1]=='@')
        {
          adj++;
        }
        // Below
        if(((y+1)<maxy) && data[y+1][x]=='@')
        {
          adj++;
        }
        if(((y+1)<maxy) && x && data[y+1][x-1]=='@')
        {
          adj++;
        }
        if(((y+1)<maxy) && ((x+1)<maxx) && data[y+1][x+1]=='@')
        {
          adj++;
        }
        // Sides
        if(x && data[y][x-1]=='@')
        {
          adj++;
        }
        if(((x+1)<maxx) && data[y][x+1]=='@')
        {
          adj++;
        }
        if(adj<4)
        {
          printf("Japp, %i:%i\n",y,x);
          sum++;
        }
      }
    }
  }

  printf("Sum: %i\n",sum);
  return 0;
}
