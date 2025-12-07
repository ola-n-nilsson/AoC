#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

int maxx;
int maxy;

long cache[256][256];

long travers(int y,int x)
{
  long ret = 0;

  if(cache[y][x]!=-1)
  {
    return cache[y][x];
  }
  
  if((y+1)==maxy)
  {
    ret = 1;
  }
  else if(((y+1)<maxy) && data[y+1][x]=='.')
  {
    ret = travers(y+1,x);
  }
  else if(((y+1)<maxy) && data[y+1][x]=='^')
  {
    if(x && data[y+1][x-1]=='.')
    {
      ret += travers(y+1,x-1);
    }
    if(((x+1)<maxx) && data[y+1][x+1]=='.')
    {
      ret += travers(y+1,x+1);
    }
  }
  cache[y][x] = ret;
  return ret;
}

int main(int argc, char* argv[])
{
  long ret;
  
  maxx = strlen(data[0]);
  maxy = sizeof(data)/sizeof(data[0]);

  memset(cache,-1,sizeof(cache));
  
  for(int x=0;x<maxx;x++)
  {
    if(data[0][x]=='S')
    {
      ret = travers(0,x);
      break;
    }
  }
  printf("Paths: %li\n",ret);
  
  return 0;
}
