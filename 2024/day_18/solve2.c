#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#if 0
const int data[] = {
#include "data2.txt"
};
int count = 12;
#else
const int data[] = {
#include "data.txt"
};
int count = 1024;
#endif

char field[128][128];
int maxy = data[1]+1;
int maxx = data[1]+1;
unsigned int cost[128][128];
int visited[128][128];
int prevy[128][128];
int prevx[128][128];

int main(int argc, char* argv[])
{
  int tcount = count;
  int exited = 0;
  
  while(!exited)  // Fast enough, so I live with it.
  {
    int ly = -1;
    int lx = -1;
    
    tcount++;
    if(!(tcount%10))
    {
      printf("At tcount: %i\n",tcount);
    }
    memset(field,'.',sizeof(field));
    memset(visited,0,sizeof(visited));
    memset(prevy,-1,sizeof(prevy));
    memset(prevx,-1,sizeof(prevx));
  
    for(int i=2;i<(2+(2*tcount));i+=2) // Should only add the last corruption, not fill and build again...
    {
      field[data[i+1]][data[i]] = '#';
      ly = data[i+1];
      lx = data[i];
    }
    for(int y=0;y<maxy;y++)
    {
      for(int x=0;x<maxx;x++)
      {
        cost[y][x] = (unsigned int)-1;
      }
    }

    {
      int sy = 0;
      int sx = 0;
      int ey = data[1];
      int ex = data[1];
      cost[0][0]=0;

      while(sy!=ey || sx!=ex)
      {
        unsigned int low = (unsigned int)-1;
    
        // Find lowest
        for(int y=0;y<maxy;y++)
        {
          for(int x=0;x<maxx;x++)
          {
            if(!visited[y][x] && field[y][x]!='#' && cost[y][x]<low)
            {
              low = cost[y][x];
              sy = y;
              sx = x;
            }
          }
        }
        if(visited[sy][sx])
        {
          break;
        }
        //Check where we could move
        // North
        if(sy && field[sy-1][sx]!='#')
        {
          if(cost[sy-1][sx]>(cost[sy][sx]+1))
          {
            cost[sy-1][sx] = (cost[sy][sx]+1);
            prevy[sy-1][sx] = sy;
            prevx[sy-1][sx] = sx;
          }
        }
        // South
        if(((sy+1)<maxy) && field[sy+1][sx]!='#')
        {
          if(cost[sy+1][sx]>(cost[sy][sx]+1))
          {
            cost[sy+1][sx] = (cost[sy][sx]+1);
            prevy[sy+1][sx] = sy;
            prevx[sy+1][sx] = sx;
          }
        }
        // West
        if(sx && field[sy][sx-1]!='#')
        {
          if(cost[sy][sx-1]>(cost[sy][sx]+1))
          {
            cost[sy][sx-1] = (cost[sy][sx]+1);
            prevy[sy][sx-1] = sy;
            prevx[sy][sx-1] = sx;
          }
        }
        // East
        if(((sx+1)<maxx) && field[sy][sx+1]!='#')
        {
          if(cost[sy][sx+1]>(cost[sy][sx]+1))
          {
            cost[sy][sx+1] = (cost[sy][sx]+1);
            prevy[sy][sx+1] = sy;
            prevx[sy][sx+1] = sx;
          }
        }
        visited[sy][sx] = 1;
      }

      if(cost[ey][ex]==-1)
      {
        printf("Not reachable when %i,%i is added\n",lx,ly);
        exited = 1;
      }
    }
  }
  return 0;
}
