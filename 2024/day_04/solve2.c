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

  if((y>0) && (x>0) && ((maxy-y)>1) && ((maxx-x)>1))
  {
    // Upright
    if(((data[y-1][x]=='M') && (data[y+1][x]=='S')) ||
       ((data[y-1][x]=='S') && (data[y+1][x]=='M')))
    {
      if(((data[y][x-1]=='M') && (data[y][x+1]=='S')) ||
         ((data[y][x-1]=='S') && (data[y][x+1]=='M')))
      {
        //cnt++;  // This apparently is not a cross...
      }
    }
    // Diagonal
    if(((data[y-1][x-1]=='M') && (data[y+1][x+1]=='S')) ||
       ((data[y-1][x-1]=='S') && (data[y+1][x+1]=='M')))
    {
      if(((data[y-1][x+1]=='M') && (data[y+1][x-1]=='S')) ||
         ((data[y-1][x+1]=='S') && (data[y+1][x-1]=='M')))
      {
        cnt++;
      }
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
      if((y>0) && (x>0) && ((maxy-y)>1) && ((maxx-x)>1) && data[y][x]=='A')
      {
        int lcnt = cnt_xmas(y,x);

        if(lcnt)
        {
          printf("A");
        }
        else
        {
          printf(".");
        }
        cnt += lcnt;
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
