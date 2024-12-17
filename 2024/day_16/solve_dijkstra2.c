#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

int maxy;
int maxx;
int sy;
int sx;
int ey;
int ex;
unsigned long moves = 0;
unsigned long best = (unsigned long)-1;

typedef enum dir_t
{
  NORTH = 0,
  EAST,
  SOUTH,
  WEST,
} dir_t;

unsigned int dist[200][200][4];
int prevy[200][200][4][4];
int prevx[200][200][4][4];
int prevd[200][200][4][4];
int pidx[200][200][4];
int visited[200][200][4];
int sumvisited = 0;


void backfrom(int y,int x,dir_t dir)
{
  if(y!=sy || x!=sx)
  {
    if(!visited[y][x][dir])
    {
      visited[y][x][dir] = 1;
    
      for(int i=0;i<pidx[y][x][dir];i++)
      {
        backfrom(prevy[y][x][dir][i],prevx[y][x][dir][i],prevd[y][x][dir][i]);
      }
    }
  }
}

int main(int argc, char* argv[])
{
  maxy = sizeof(data)/sizeof(data[0]);
  maxx = strlen(data[0]);

  memset(prevy,0,sizeof(prevy));
  memset(prevx,0,sizeof(prevx));
  memset(prevd,0,sizeof(prevd));
  memset(pidx,0,sizeof(pidx));
  memset(visited,0,sizeof(visited));

  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      for(int i=0;i<4;i++)
      {
        dist[y][x][i] = (unsigned int)-1;
      }
      switch(data[y][x])
      {
        case 'S':
          sy=y;
          sx=x;
          break;
        case 'E':
          ey=y;
          ex=x;
          break;
      }
    }
  }

  dist[sy][sx][EAST]=0;

  {
    while(sumvisited<(maxy*maxx*4))
    {
      int y;
      int x;
      int dir;
      unsigned int lowest = (unsigned int)-1;
      int dy = 0;
      int dx = 0;

      // Start dumb, just find the node with lowest cost
      for(int yi=0;yi<maxy;yi++)
      {
        for(int xi=0;xi<maxx;xi++)
        {
          if(data[yi][xi]!='#') // No need to look here
          {
            for(int ii=0;ii<4;ii++)
            {
              if(!visited[yi][xi][ii] && dist[yi][xi][ii]<lowest)
              {
                lowest = dist[yi][xi][ii];
                y = yi;
                x = xi;
                dir = ii;
              }
            }
          }
        }
      }
      if((y+dy>=0) && (x+dx>=0) && ((y+dy)<maxy) && ((x+dx)<maxx) && (data[y+dy][x+dx]=='#'))
      {
        //At a stone, skip.
        visited[y][x][dir] = 1;
        sumvisited++;
        continue;
      }
      //printf("Looking at %i:%i %i\n",);
      
      for(int i=0;i<4;i++)
      {
        if(i!=dir && !visited[y][x][dir])
        {
          int cost = 0;

          switch(dir)
          {
            case NORTH:
              {
                int costs[] = {0,1000,2000,1000};
                cost = costs[i];
              }
              break;
            case EAST:
              {
                int costs[] = {1000,0,1000,2000};
                cost = costs[i];
              }
              break;
            case SOUTH:
              {
                int costs[] = {2000,1000,0,1000};
                cost = costs[i];
              }
              break;
            case WEST:
              {
                int costs[] = {1000,2000,1000,0};
                cost = costs[i];
              }
              break;
          }
          if(dist[y][x][dir]+cost==dist[y][x][i])
          {
            prevy[y][x][i][pidx[y][x][i]] = y;
            prevx[y][x][i][pidx[y][x][i]] = x;
            prevd[y][x][i][pidx[y][x][i]] = dir;
            pidx[y][x][i]++;
          }
          else if(dist[y][x][dir]+cost<dist[y][x][i])
          {
            dist[y][x][i] = dist[y][x][dir]+cost;
            prevy[y][x][i][0] = y;
            prevx[y][x][i][0] = x;
            prevd[y][x][i][0] = dir;
            pidx[y][x][i] = 1;
          }
        }
      }

      switch(dir)
      {
        case NORTH:
          dy = -1;
          break;
        case EAST:
          dx = 1;
          break;
        case SOUTH:
          dy = 1;
          break;
        case WEST:
          dx = -1;
          break;
      }
      // Straight ahead
      if((y+dy>=0) && (x+dx>=0) && ((y+dy)<maxy) && ((x+dx)<maxx) && (data[y+dy][x+dx]!='#'))
      {
        if(dist[y+dy][x+dx][dir]==(dist[y][x][dir]+1))
        {
          prevy[y+dy][x+dx][dir][pidx[y+dy][x+dx][dir]] = y;
          prevx[y+dy][x+dx][dir][pidx[y+dy][x+dx][dir]] = x;
          prevd[y+dy][x+dx][dir][pidx[y+dy][x+dx][dir]] = dir;
          pidx[y+dy][x+dx][dir]++;
        }
        else if(dist[y+dy][x+dx][dir]>(dist[y][x][dir]+1))
        {
          dist[y+dy][x+dx][dir] = dist[y][x][dir]+1;
          prevy[y+dy][x+dx][dir][0] = y;
          prevx[y+dy][x+dx][dir][0] = x;
          prevd[y+dy][x+dx][dir][0] = dir;
          pidx[y+dy][x+dx][dir]++;
        }
      }
      visited[y][x][dir] = 1;
      sumvisited++;
    }
  }

  // Use our dist to find all paths with same costs
  {
    int y = ey;
    int x = ex;
    int dir = NORTH;

    memset(visited,0,sizeof(visited));
    sumvisited = 0;

    for(int i=1;i<4;i++)
    {
      if(dist[ey][ex][i]<dist[ey][ex][dir])
      {
        dir = i;
      }
    }
    
    backfrom(y,x,dir);
    sumvisited++;  // For the start.

    for(int yi=0;yi<maxy;yi++)
    {
      for(int xi=0;xi<maxx;xi++)
      {
        if(visited[yi][xi][NORTH] ||
           visited[yi][xi][EAST] ||
           visited[yi][xi][SOUTH] ||
           visited[yi][xi][WEST])
        {
          printf("O");
          sumvisited++;
        }
        else
        {
          printf("%c",data[yi][xi]);
        }
      }
      printf("\n");
    }
        
    printf("Back gave: %i\n",sumvisited);
  }
  return 0;
}
