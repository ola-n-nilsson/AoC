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
unsigned int costs[256][256];
int visited[256][256];
int prevy[256][256];
int prevx[256][256];
int path[256][256];

int racetime(void)
{
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

    if(data[y-1][x]!='#')
    {
      if(costs[y-1][x]>(costs[y][x]+1))
      {
        costs[y-1][x] = costs[y][x]+1;
        lowy[lowidx] = y-1;
        lowx[lowidx] = x;
        prevy[y-1][x] = y;
        prevx[y-1][x] = x;
        lowidx++;
      }
    }
    if(data[y+1][x]!='#')
    {
      if(costs[y+1][x]>(costs[y][x]+1))
      {
        costs[y+1][x] = costs[y][x]+1;
        lowy[lowidx] = y+1;
        lowx[lowidx] = x;
        prevy[y+1][x] = y;
        prevx[y+1][x] = x;
        lowidx++;
      }
    }
    if(data[y][x-1]!='#')
    {
      if(costs[y][x-1]>(costs[y][x]+1))
      {
        costs[y][x-1] = costs[y][x]+1;
        lowy[lowidx] = y;
        lowx[lowidx] = x-1;
        prevy[y][x-1] = y;
        prevx[y][x-1] = x;
        lowidx++;
      }
    }
    if(data[y][x+1]!='#')
    {
      if(costs[y][x+1]>(costs[y][x]+1))
      {
        costs[y][x+1] = costs[y][x]+1;
        lowy[lowidx] = y;
        lowx[lowidx] = x+1;
        prevy[y][x+1] = y;
        prevx[y][x+1] = x;
        lowidx++;
      }
    }
    visited[y][x] = 1;
  }
  return costs[ey][ex];
}

int manhattan(int y,int x,int yy,int xx)
{
  int ret = abs(yy-y)+abs(xx-x);

  return ret;
}
int shortcuts(int yy,int xx)
{
  int cnt = 0;
  int y = yy-21;  // Silly of by one error. We check Manhattan later, so go big!
  int x = xx-21;
  int sly = yy+21;
  int slx = xx+21;
  int rex;

  if(y<1)
  {
    y=1;
  }
  if(x<1)
  {
    x=1;
  }
  if((sly+1)>=maxy)
  {
    sly = maxy-1;
  }
  if((slx+1)>=maxx)
  {
    slx = maxx-1;
  }

  rex = x;
  for(;y<sly;y++)
  {
    for(x=rex;x<slx;x++)
    {
      int man = manhattan(y,x,yy,xx);

      if((man<=20) && path[y][x] && ((costs[y][x]+man)<costs[yy][xx]))
      {
        int save = costs[yy][xx] - costs[y][x] - man;

        if(save>=100)
        {
          //printf("Found %i shortcut for %i:%i\n",save,y,x);
          cnt++;
        }
      }
    }
  }
  return cnt;
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
  printf("Race takes: %ips\n",(rtime = racetime()));

  // Prepair the path
  {
    int y = ey;
    int x = ex;
    
    memset(path,0,sizeof(path));
    while(y!=sy || x!=sx)
    {
      int ny;
      
      path[y][x] = 1;
      ny = prevy[y][x];
      x = prevx[y][x];
      y = ny;
    }
    path[sy][sx] = 1;
  }

  // Walk the path and check for shortcuts
  {
    int y = ey;
    int x = ex;
    
    while(y!=sy || x!=sx)
    {
      int ny;
      cnt += shortcuts(y,x);
      ny = prevy[y][x];
      x = prevx[y][x];
      y = ny;
    }
    cnt += shortcuts(y,x);  // Also for sy:sx...
  }
  printf("Shortcut >=100 count: %i\n",cnt);

#if 0
  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      if(path[y][x])
      {
        printf("O");
      }
      else
      {
        printf("%c",data[y][x]);
      }
    }
    printf("\n");
  }
#endif
  
  return 0;
}

// Too low: 980484
//          986082
