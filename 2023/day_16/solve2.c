#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef enum {
  NORTH = 0,
  EAST,
  SOUTH,
  WEST,
} dir_t;

char* data[] = {
#include "data.txt"
};

int maxy;
int maxx;
int energized[120][120];
int visited[120][120][4];

int getnext(int y,int x, dir_t dir, int* yy, int* xx)
{
  *yy = y;
  *xx = x;
  
  switch(dir)
  {
    case NORTH:
      if(y)
      {
        (*yy)--;
      }
      else
      {
        return 0;
      }
      break;
    case EAST:
      if(x<(maxx-1))
      {
        (*xx)++;
      }
      else
      {
        return 0;
      }
      break;
    case SOUTH:
      if(y<(maxy-1))
      {
        (*yy)++;
      }
      else
      {
        return 0;
      }
      break;
    case WEST:
      if(x)
      {
        (*xx)--;
      }
      else
      {
        return 0;
      }
      break;
    default:
      printf("Ooops!\n");
      exit(-1);
      break;
  }

  return 1;
}

void energize(int y,int x,dir_t dir)
{
  int yy;
  int xx;
  
  energized[y][x] = 1;
  if(visited[y][x][dir])
  {
    return;
  }
  visited[y][x][dir] = 1;

  switch(data[y][x])
  {
    case '.':
      if(getnext(y,x,dir,&yy,&xx))
      {
        energize(yy,xx,dir);
      }
      break;
    case '/':
      switch(dir)
      {
        case NORTH:
          if(getnext(y,x,EAST,&yy,&xx))
          {
            energize(yy,xx,EAST);
          }
          break;
        case EAST:
          if(getnext(y,x,NORTH,&yy,&xx))
          {
            energize(yy,xx,NORTH);
          }
          break;
        case SOUTH:
          if(getnext(y,x,WEST,&yy,&xx))
          {
            energize(yy,xx,WEST);
          }
          break;
        case WEST:
          if(getnext(y,x,SOUTH,&yy,&xx))
          {
            energize(yy,xx,SOUTH);
          }
          break;
      }
      break;
    case '\\':
      switch(dir)
      {
        case NORTH:
          if(getnext(y,x,WEST,&yy,&xx))
          {
            energize(yy,xx,WEST);
          }
          break;
        case EAST:
          if(getnext(y,x,SOUTH,&yy,&xx))
          {
            energize(yy,xx,SOUTH);
          }
          break;
        case SOUTH:
          if(getnext(y,x,EAST,&yy,&xx))
          {
            energize(yy,xx,EAST);
          }
          break;
        case WEST:
          if(getnext(y,x,NORTH,&yy,&xx))
          {
            energize(yy,xx,NORTH);
          }
          break;
      }
      break;
    case '|':
      switch(dir)
      {
        case EAST:
        case WEST:
          if(getnext(y,x,NORTH,&yy,&xx))
          {
            energize(yy,xx,NORTH);
          }
          if(getnext(y,x,SOUTH,&yy,&xx))
          {
            energize(yy,xx,SOUTH);
          }
          break;
        case NORTH:
          if(getnext(y,x,NORTH,&yy,&xx))
          {
            energize(yy,xx,NORTH);
          }
          break;
        case SOUTH:
          if(getnext(y,x,SOUTH,&yy,&xx))
          {
            energize(yy,xx,SOUTH);
          }
          break;
      }
      break;
    case '-':
      switch(dir)
      {
        case NORTH:
        case SOUTH:
          if(getnext(y,x,WEST,&yy,&xx))
          {
            energize(yy,xx,WEST);
          }
          if(getnext(y,x,EAST,&yy,&xx))
          {
            energize(yy,xx,EAST);
          }
          break;
        case EAST:
          if(getnext(y,x,EAST,&yy,&xx))
          {
            energize(yy,xx,EAST);
          }
          break;
        case WEST:
          if(getnext(y,x,WEST,&yy,&xx))
          {
            energize(yy,xx,WEST);
          }
          break;
      }
      break;
    default:
      printf("Ooops!\n");
      exit(-1);
      break;
  }
}

int count(void)
{
  int cnt = 0;
  
  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      if(energized[y][x])
      {
        cnt++;
      }
    }
  }
  return cnt;
}

int main(int argc, char* argv[])
{
  maxy = sizeof(data)/sizeof(data[0]);
  maxx = strlen(data[0]);

  printf("Field size %i:%i\n",maxy,maxx);
  
  for(int y=0;y<maxy;y++) // I had to modify data and wanted to check I did it right... \ to two...
  {
    if(strlen(data[y])!=maxx)
    {
      printf("Ooops!\n");
      exit(-1);
    }
  }

  {
    int maxcnt = 0;
    int cnt;
    
    for(int xx=0;xx<maxx;xx++)
    {
      // SOUTH
      memset(energized,0,sizeof(energized));
      memset(visited,0,sizeof(visited));
      energize(0,xx,SOUTH);
      cnt = count();
      if(cnt>maxcnt)
      {
        maxcnt = cnt;
      }
      // NORTH
      memset(energized,0,sizeof(energized));
      memset(visited,0,sizeof(visited));
      energize(maxy-1,xx,NORTH);
      cnt = count();
      if(cnt>maxcnt)
      {
        maxcnt = cnt;
      }
    }
    for(int yy=0;yy<maxy;yy++)
    {
      // EAST
      memset(energized,0,sizeof(energized));
      memset(visited,0,sizeof(visited));
      energize(yy,0,EAST);
      cnt = count();
      if(cnt>maxcnt)
      {
        maxcnt = cnt;
      }
      // WEST
      memset(energized,0,sizeof(energized));
      memset(visited,0,sizeof(visited));
      energize(yy,maxx-1,WEST);
      cnt = count();
      if(cnt>maxcnt)
      {
        maxcnt = cnt;
      }
    }
    printf("Max: %i\n",maxcnt);
  }
  
  return 0;
}
