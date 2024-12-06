#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

char visited[200][200];

int maxy;
int maxx;
int starty = -1;
int startx = -1;

int infield(int y,int x)
{
  return ((y>=0) && (x>=0) && (y<maxy) && (x<maxx));
}

int main(int argc, char* argv[])
{
  maxy = sizeof(data)/sizeof(data[0]);
  maxx = strlen(data[0]);
  int loopcnt = 0;
  
  memset(visited,0,sizeof(visited));
  
  for(int y=0;(y<maxy)&&(startx==-1);y++)
  {
    for(int x=0;x<maxx;x++)
    {
      if(data[y][x]=='^')
      {
        starty = y;
        startx = x;
        break;
      }
    }
  }
  printf("Field %i:%i start %i:%i\n",maxy,maxx,starty,startx);

  for(int ey=0;ey<maxy;ey++)
  {
    for(int ex=0;ex<maxx;ex++)
    {
      int y=starty;
      int x=startx;
      int dy=-1;
      int dx=0;
      int visitcnt = 0;
      int steps = 0;

      if((starty==ey) && (startx==ex))
      {
        continue;
      }
      
      do
      {
        if(visited[y][x]!='X')
        {
          visited[y][x]='X';
          visitcnt++;
          steps = 0;
        }
        if(steps==130*130)
        {
          loopcnt++;
          break;
        }
        y+=dy;
        x+=dx;
        steps++;
        if(infield(y,x) && ((data[y][x]=='#') || ((y==ey) && (x==ex))))
        {
          y-=dy;
          x-=dx;
          steps--;
          switch(dy)
          {
            case 1:
              if(dx!=0)
              {
                exit(-1);
              }
              dy=0;
              dx=-1;
              break;
            case 0:
              switch(dx)
              {
                case 1:
                  dy=1;
                  dx=0;
                  break;
                case -1:
                  dy=-1;
                  dx=0;
                  break;
                default:
                  exit(-1);
              }
              break;
            case -1:
              if(dx!=0)
              {
                exit(-1);
              }
              dy=0;
              dx=1;
              break;
            default:
              exit(-1);
          }
        }
      } while(infield(y,x));
    }
  }
  printf("Places with loops: %i\n",loopcnt);
  return 0;
}
