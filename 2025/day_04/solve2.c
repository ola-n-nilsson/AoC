#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int maxx;
int maxy;

char* data[] = {
#include "data.txt"
};

int main(int argc, char* argv[])
{
  int sum = 0;
  int lastsum = -1;
  char removed[256][256];
  char nowremoved[256][256];
  
  maxy = sizeof(data)/sizeof(data[0]);
  maxx = strlen(data[0]);
  memset(removed,0,sizeof(removed));

  while(lastsum!=sum)
  {
    lastsum = sum;
    memcpy(removed,nowremoved,sizeof(removed));
    
    for(int y=0;y<maxy;y++)
    {
      for(int x=0;x<maxx;x++)
      {

        if(data[y][x]=='@')
        {
          int empty = 0;
        
          // Above
          if(y)
          {
            if(data[y-1][x]=='.' || removed[y-1][x])
            {
              empty++;
            }
          }
          else
          {
            empty++;
          }
          if(y && x)
          {
            if(data[y-1][x-1]=='.' || removed[y-1][x-1])
            {
              empty++;
            }
          }
          else
          {
            empty++;
          }
          if(y && ((x+1)<maxx))
          {
            if(data[y-1][x+1]=='.' || removed[y-1][x+1])
            {
              empty++;
            }
          }
          else
          {
            empty++;
          }
          // Below
          if(((y+1)<maxy))
          {
            if(  data[y+1][x]=='.' || removed[y+1][x])
            {
              empty++;
            }
          }
          else
          {
            empty++;
          }
          if(((y+1)<maxy) && x )
          {
            if( data[y+1][x-1]=='.'  || removed[y+1][x-1])
            {
              empty++;
            }
          }
          else
          {
            empty++;
          }
          if(((y+1)<maxy) && ((x+1)<maxx) )
          {
            if( data[y+1][x+1]=='.'  || removed[y+1][x+1])
            {
              empty++;
            }
          }
          else
          {
            empty++;
          }
          // Sides
          if(x)
          {
            if(data[y][x-1]=='.'  || removed[y][x-1])
            {
              empty++;
            }
          }
          else
          {
            empty++;
          }
          if(((x+1)<maxx))
          {
            if(data[y][x+1]=='.'  || removed[y][x+1])
            {
              empty++;
            }
          }
          else
          {
            empty++;
          }
          
        
          if(empty>=5)
          {
            if(!removed[y][x])
            {
              printf("Japp, %i:%i\n",y,x);
              nowremoved[y][x] = 1;
              sum++;
            }
          }
        }
      }
    }
    printf("Removed: %i (%i %i)\n",sum-lastsum,sum,lastsum);
  }

  printf("Sum: %i\n",sum);
  return 0;
}
