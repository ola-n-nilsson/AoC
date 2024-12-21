#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

int maxx;
int maxy;
int sy;
int sx;
int ey;
int ex;

int racetime(int ry,int rx)
{
  unsigned int costs[200][200];
  int visited[200][200];
  int y = sy;
  int x = sx;
  int lowy[200*200];
  int lowx[200*200];
  int lowidx = 0;
  
  memset(costs,-1,sizeof(costs));
  memset(visited,0,sizeof(visited));
  costs[y][x]=0;

  while(y!=ey || x!=ex)
  {
#if 0
    unsigned lowest = (unsigned int)-1;
    for(int yy=1;yy+1<maxy;yy++)
    {      
      for(int xx=1;xx+1<maxx;xx++)
      {
        if(!visited[yy][xx] && (costs[yy][xx]<lowest))
        {
          lowest = costs[yy][xx];
          y = yy;
          x = xx;
        }
      }
    }
#else
    if(lowidx>2)
    {
      unsigned lowest = (unsigned int)-1;
      int cpos;
      
      for(int i=0;i<lowidx;i++)
      {
        if(costs[lowy[i]][lowx[i]]<lowest)
        {
          lowest = costs[lowy[i]][lowx[i]];
          y = lowy[i];
          x = lowx[i];
          cpos = i;
        }
      }
      memcpy(&lowy[cpos],&lowy[cpos+1],sizeof(lowy[0])*(lowidx-cpos));
      memcpy(&lowx[cpos],&lowx[cpos+1],sizeof(lowx[0])*(lowidx-cpos));
      lowidx--;
    }
    if(lowidx)
    {
      if(lowidx==1)
      {
        y = lowy[0];
        x = lowx[0];
        lowidx--;
      } else if(costs[lowy[0]][lowx[0]]<costs[lowy[1]][lowx[1]])
      {
        y = lowy[0];
        x = lowx[0];
        lowy[0] = lowy[1];
        lowx[0] = lowx[1];
        lowidx = 1;
      }
      else
      {
        y = lowy[1];
        x = lowx[1];
        lowidx = 1;
      }
    }
#endif
    if(data[y-1][x]!='#' || ((y-1)==ry && x==rx))
    {
      if(costs[y-1][x]>(costs[y][x]+1))
      {
        costs[y-1][x] = costs[y][x]+1;
        lowy[lowidx] = y-1;
        lowx[lowidx] = x;
        lowidx++;
      }
    }
    if(data[y+1][x]!='#' || ((y+1)==ry && x==rx))
    {
      if(costs[y+1][x]>(costs[y][x]+1))
      {
        costs[y+1][x] = costs[y][x]+1;
        lowy[lowidx] = y+1;
        lowx[lowidx] = x;
        lowidx++;
      }
    }
    if(data[y][x-1]!='#' || (y==ry && (x-1)==rx))
    {
      if(costs[y][x-1]>(costs[y][x]+1))
      {
        costs[y][x-1] = costs[y][x]+1;
        lowy[lowidx] = y;
        lowx[lowidx] = x-1;
        lowidx++;
      }
    }
    if(data[y][x+1]!='#' || (y==ry && (x+1)==rx))
    {
      if(costs[y][x+1]>(costs[y][x]+1))
      {
        costs[y][x+1] = costs[y][x]+1;
        lowy[lowidx] = y;
        lowx[lowidx] = x+1;
        lowidx++;
      }
    }
    visited[y][x] = 1;
  }
  return costs[ey][ex];
}

int main(int argc, char* argv[])
{
  int rtime = 0;
  int cnt = 0;
  maxx = strlen(data[0]);
  maxy = sizeof(data)/sizeof(data[0]);
  
  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      switch(data[y][x])
      {
        case 'S':
          sy = y;
          sx = x;
          break;
        case 'E':
          ey = y;
          ex = x;
          break;
      }
    }
  }

  printf("Field %i:%i Start: %i:%i End %i:%i\n",maxy,maxx,sy,sx,ey,ex);

  printf("Race takes: %ips\n",(rtime = racetime(-1,-1)));

  for(int y=1;(y+1)<maxy;y++)
  {
    for(int x=1;(x+1)<maxx;x++)
    {
      if(data[y][x]=='#')
      {
        int ctime = racetime(y,x);

        if(rtime>ctime)
        {
          printf("%i:%i saves %ips\n",y,x,rtime-ctime);
        }
        if((rtime-ctime)>=100)
        {
          cnt++;
        }
      }
    }
  }
  printf("%i saves over 100ps\n",cnt);
  return 0;
}

// 1339 is wrong >100, should be >=100 and we get 1365!
