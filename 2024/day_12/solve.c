#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

int fill[200][200];

int area[200*200];
int per[200*200];
int idx = 0;

int maxy;
int maxx;

void fillrec(char c,int y,int x,int *rarea,int *rper)
{
  if(y>0)
  {
    if((data[y-1][x]==c) && (!fill[y-1][x]))
    {
      fill[y-1][x] = 1;
      fillrec(c,y-1,x,rarea,rper);
    }
  }
  if((y+1)<maxy)
  {
    if((data[y+1][x]==c) && (!fill[y+1][x]))
    {
      fill[y+1][x] = 1;
      fillrec(c,y+1,x,rarea,rper);
    }
  }
  if(x>0)
  {
    if((data[y][x-1]==c) && (!fill[y][x-1]))
    {
      fill[y][x-1] = 1;
      fillrec(c,y,x-1,rarea,rper);
    }
  }
  if((x+1)<maxx)
  {
    if((data[y][x+1]==c) && (!fill[y][x+1]))
    {
      fill[y][x+1] = 1;
      fillrec(c,y,x+1,rarea,rper);
    }
  }
  (*rarea)++;
  if((!y) || (data[y-1][x]!=c))
  {
    (*rper)++;
  }
  if(((y+1)==maxy) || (data[y+1][x]!=c))
  {
    (*rper)++;
  }
  if((!x) || (data[y][x-1]!=c))
  {
    (*rper)++;
  }
  if(((x+1)==maxx) || (data[y][x+1]!=c))
  {
    (*rper)++;
  }
  return;
}

void fillregion(int y,int x)
{
  int rarea = 0;
  int rper = 0;

  fill[y][x] = 1;
  fillrec(data[y][x],y,x,&rarea,&rper);
  printf("Region at %i:%i %c a: %i p: %i\n",y,x,data[y][x],rarea,rper);
  area[idx] = rarea;
  per[idx] = rper;
  idx++;
  return;
}

int main(int argc, char* argv[])
{
  unsigned long cost = 0;
  
  maxy = (sizeof(data)/sizeof(data[0]));
  maxx = strlen(data[0]);

  memset(fill,0,sizeof(fill));
  memset(area,0,sizeof(area));
  memset(per,0,sizeof(per));
  
  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      if(!fill[y][x])
      {
        fillregion(y,x);
      }
    }
  }
  for(int i=0;i<idx;i++)
  {
    cost+=area[i]*per[i];
  }
  printf("Tot cost: %lu\n",cost);
  return 0;
}
