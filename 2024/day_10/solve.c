#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

int reached[100][100];

int maxy;
int maxx;

void search(int y,int x,int *paths)
{
  int next = data[y][x]+1;

  if(data[y][x]=='9')
  {
    (*paths)++;
    reached[y][x]++;
    return;
  }
  if((y>0) && data[y-1][x]==next)
  {
    search(y-1,x,paths);
  }
  if((x>0) && data[y][x-1]==next)
  {
    search(y,x-1,paths);
  }
  if(((y+1)<maxy) && data[y+1][x]==next)
  {
    search(y+1,x,paths);
  }
  if(((x+1)<maxx) && data[y][x+1]==next)
  {
    search(y,x+1,paths);
  }
  return;
}

int main(int argc, char* argv[])
{
  unsigned long sum = 0;
  unsigned long psum = 0;
  
  maxy = sizeof(data)/sizeof(data[0]);
  maxx = strlen(data[0]);
  
  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      if(data[y][x]=='0')
      {
        int paths = 0;
        int poscnt = 0;
        
        memset(reached,0,sizeof(reached));
        search(y,x,&paths);

        for(int y2=0;y2<maxy;y2++)
        {
          for(int x2=0;x2<maxx;x2++)
          {
            if(reached[y2][x2])
            {
              poscnt++;
            }
          }
        }

        sum+=poscnt;
        psum+=paths;
        printf("Pos %i:%i reached %i through %i paths\n",y,x,poscnt,paths);
      }
    }
  }
  printf("Trailhead sum: %lu\n",sum);
  printf("Path sum: %lu\n",psum);
  return 0;
}
