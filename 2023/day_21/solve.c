#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define STOP (64)
char* data[] = {
#include "data.txt"
};

int maxy;
int maxx;

char visited[256][256];
int nexty[256*256];
int nextx[256*256];
int nextidx = 0;

int prepy[256*256];
int prepx[256*256];
int idx = 0;

void insert(int y, int x)
{
  int i;
  
  for(i=0;i<idx;i++)
  {
    if((prepy[i]==y) && (prepx[i]==x))
    {
      return;
    }
  }
  prepy[i]=y;
  prepx[i]=x;
  idx++;
  return;
}

void walk(int step)
{
  
  if(step==STOP)
  {
    // Don't walk any more.
    for(int i=0;i<nextidx;i++)
    {
      visited[nexty[i]][nextx[i]] = 'O';
    }
    return;
  }

  // Walk
  {
    int y;
    int x;
    
    for(int i=0;i<nextidx;i++)
    {
      y = nexty[i];
      x = nextx[i];
      if(y && ((data[y-1][x]=='.') || (data[y-1][x]=='S')) && ((!(visited[y-1][x]))))
      {
        //        printf("At step %i visit %i:%i\n",step,y-1,x);
        insert(y-1,x);
      }
      if(x && ((data[y][x-1]=='.') || (data[y][x-1]=='S')) && (!(visited[y][x-1])))
      {
        //        printf("At step %i visit %i:%i\n",step,y,x-1);
        insert(y,x-1);
      }
      if(((y+1)<maxy) && ((data[y+1][x]=='.') || (data[y+1][x]=='S')) && ((!(visited[y+1][x]))))
      {
        //        printf("At step %i visit %i:%i\n",step,y+1,x);
        insert(y+1,x);
      }
      if(((x+1)<maxx) && ((data[y][x+1]=='.') || (data[y][x+1]=='S')) && ((!(visited[y][x+1]))))
      {
        //        printf("At step %i visit %i:%i\n",step,y,x+1);
        insert(y,x+1);
      }
    }
  }
  step++;
  memcpy(nexty,prepy,sizeof(int)*idx);
  memcpy(nextx,prepx,sizeof(int)*idx);
  nextidx = idx;
  idx = 0;
  walk(step);
}


int main(int argc, char* argv[])
{
  int starty = -1;
  int startx = -1;
  
  maxy = sizeof(data)/sizeof(data[0]);
  maxx = strlen(data[0]);

  memset(visited,0,sizeof(visited));
  
  for(int y=0;(y<maxy) && (starty==-1);y++)
  {
    for(int x=0;x<maxx;x++)
    {
      if(data[y][x] == 'S')
      {
        starty=y;
        startx=x;
        break;
      }
    }
  }

  printf("Field size: %i:%i Start: %i,%i\n",maxy,maxx,starty,startx);

  nexty[0] = starty;
  nextx[0] = startx;
  nextidx++;
  
  walk(0);

  {
    int cnt = 0;

    for(int y=0;y<maxy;y++)
    {
      for(int x=0;x<maxx;x++)
      {
        if(visited[y][x] == 'O')
        {
          printf("O");
          cnt++;
        }
        else
        {
          printf("%c",data[y][x]);
        }
      }
      printf("\n");
    }
    printf("\nCount: %i\n",cnt);
  }
  
  return 0;
}

// 314 wrong
