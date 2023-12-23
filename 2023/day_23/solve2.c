#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

int maxy;
int maxx;

int visited[256][256];

int maxpath = 0;

void walk(int y, int x, int ey, int ex, int steps)
{
  if(y==ey && x==ex)
  {
    printf("Path found! %i steps (%i)\n",steps,maxpath); // Well, when I posted my result the code had not stopped running. I just took the stable max...
    if(steps>maxpath)
    {
      maxpath = steps;
    }
    return;
  }

  visited[y][x] = 1;
  steps++;

  if(y && !visited[y-1][x])
  {
    switch(data[y-1][x])
    {
      case '.':
      case '^':
      case '<':
      case '>':
      case 'v':
        walk(y-1,x,ey,ex,steps);
        break;
    }
  }
  if(x && !visited[y][x-1])
  {
    switch(data[y][x-1])
    {
      case '.':
      case '^':
      case '<':
      case '>':
      case 'v':
        walk(y,x-1,ey,ex,steps);
        break;
    }
  }
  if(y<(maxy-1) && !visited[y+1][x])
  {
    switch(data[y+1][x])
    {
      case '.':
      case '^':
      case '<':
      case '>':
      case 'v':
        walk(y+1,x,ey,ex,steps);
        break;
    }
  }
  if(x<(maxx-1) && !visited[y][x+1])
  {
    switch(data[y][x+1])
    {
      case '.':
      case '^':
      case '<':
      case '>':
      case 'v':
        walk(y,x+1,ey,ex,steps);
        break;
    }
  }
  visited[y][x] = 0;
  return;
}

int main(int argc, char* argv[])
{
  int startx = 1;
  int starty = 0;
  int endy;
  int endx;
  
  maxx = strlen(data[0]);
  maxy = sizeof(data)/sizeof(data[0]);

  endy=maxy-1;
  endx=maxx-2;

  memset(visited,0,sizeof(visited));

  walk(starty,startx,endy,endx,0);
  
  printf("Max path: %i\n",maxpath);
  
  return 0;
}
