#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};
int maxx;
int maxy;

int check(int y, int x, int len)
{
  // To the left
  if(x>0)
  {
    if(data[y][x-1]!='.')
    {
      return 0;
    }
  }
  // To the right
  if((x+len)<maxx)
  {
    if(data[y][x+len]!='.')
    {
      return 0;
    }
  }
  //Above?
  if(y>0)
  {
    int start = x-1;
    int end = x+len;

    if(start<0)
    {
      start = 0;
    }
    if(end>=maxx)
    {
      end = maxx-1;
    }
    for(int xx=start;xx<=end;xx++)
    {
      if(data[y-1][xx]!='.')
      {
        return 0;
      }
    }
  }
  //Below?
  if((y+1)<maxy)
  {
    int start = x-1;
    int end = x+len;

    if(start<0)
    {
      start = 0;
    }
    if(end>=maxx)
    {
      end = maxx-1;
    }
    for(int xx=start;xx<=end;xx++)
    {
      if(data[y+1][xx]!='.')
      {
        return 0;
      }
    }
  }
  return 1;
}

int find(int y, int x, int* nbr_p)
{
  int len = 0;
  *nbr_p = 0;
  
  do
  {
    if(data[y][x+len]>='0' && data[y][x+len]<='9')
    {
      *nbr_p *= 10;
      *nbr_p += (data[y][x+len] - '0');
      len++;
    }
  } while (((x+len)<maxx) && ((data[y][x+len]>='0' && data[y][x+len]<='9')));
  return len;
}

int main(int argc, char* argv[])
{
  maxx = strlen(data[0]);
  maxy = sizeof(data)/sizeof(data[0]);
  unsigned long sum = 0;
  
  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;)
    {
      int nbr = 0;
      int len = find(y,x, &nbr);
      
      if(len)
      {
        if(!check(y,x,len))
        {
          printf("Adding %i:%i nbr: %i\n",y,x,nbr);
          sum += nbr;
        }
        x+=len;
      }
      else
      {
        x++;
      }
    }
  }
  printf("Sum: %lu\n",sum);
  return 0;
}


// Part 1: 55707 wrong
