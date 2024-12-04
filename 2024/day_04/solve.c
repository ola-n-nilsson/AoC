#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

int maxy;
int maxx;

int cnt_xmas(int y, int x)
{
  int cnt = 0;
  //Right
  if((maxx-x)>3)
  {
    if((data[y][x+1]=='M') &&
       (data[y][x+2]=='A') &&
       (data[y][x+3]=='S'))
    {
      cnt++;
    }
  }
  //Left
  if(x>2)
  {
    if((data[y][x-1]=='M') &&
       (data[y][x-2]=='A') &&
       (data[y][x-3]=='S'))
    {
      cnt++;
    }
  }
  //Up
  if(y>2)
  {
    if((data[y-1][x]=='M') &&
       (data[y-2][x]=='A') &&
       (data[y-3][x]=='S'))
    {
      cnt++;
    }
  }
  //Down
  if((maxy-y)>3)
  {
    if((data[y+1][x]=='M') &&
       (data[y+2][x]=='A') &&
       (data[y+3][x]=='S'))
    {
      cnt++;
    }
  }
  //SE +1 +1
  if(((maxy-y)>3) && ((maxx-x)>3))
  {
    if((data[y+1][x+1]=='M') &&
       (data[y+2][x+2]=='A') &&
       (data[y+3][x+3]=='S'))
    {
      cnt++;
    }
  }
  //NW -1 -1
  if((y>2) && (x>2))
  {
    if((data[y-1][x-1]=='M') &&
       (data[y-2][x-2]=='A') &&
       (data[y-3][x-3]=='S'))
    {
      cnt++;
    }
  }
  //NE -1 +1
  if((y>2) && ((maxx-x)>3))
  {
    if((data[y-1][x+1]=='M') &&
       (data[y-2][x+2]=='A') &&
       (data[y-3][x+3]=='S'))
    {
      cnt++;
    }
  }
  //SW +1 -1
  if(((maxy-y)>3) && (x>2))
  {
    if((data[y+1][x-1]=='M') &&
       (data[y+2][x-2]=='A') &&
       (data[y+3][x-3]=='S'))
    {
      cnt++;
    }
  }
  return cnt;
}

int main(int argc, char* argv[])
{
  int cnt = 0;
  
  maxx = strlen(data[0]);
  maxy = sizeof(data)/sizeof(data[0]);

  printf("Grid size: %i:%i\n",maxy,maxx);
  
  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      if(data[y][x]=='X')
      {
        printf("X");
        cnt += cnt_xmas(y,x);
      }
      else
      {
        printf(".");
      }
    }
    printf("\n");
  }
  printf("Count: %i\n",cnt);
  return 0;
}
