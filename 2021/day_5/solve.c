#include <stdio.h>
#include <string.h>

const int lines[][4] = {
#include "input.c"
};

#define MAP_SIZE 990
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

int main(int argc,char* argv[])
{
  int i,x,y;
  int map[MAP_SIZE][MAP_SIZE];

  memset(map,0,sizeof(map));
  
  for(i=0;i<(sizeof(lines)/sizeof(lines[0]));i++)
  {
    if((lines[i][0] == lines[i][2]) || (lines[i][1] == lines[i][3]))
    {
      if((lines[i][0] == lines[i][2]))
      {
        //same X
        for(y=MIN(lines[i][1], lines[i][3]);y<=MAX(lines[i][1], lines[i][3]);y++)
        {
          map[y][lines[i][0]] += 1;
        }
      }
      else
      {
        //same Y
        for(x=MIN(lines[i][0], lines[i][2]);x<=MAX(lines[i][0], lines[i][2]);x++)
        {
          map[lines[i][1]][x] += 1;
        }
      }
    }
  }

  int cnt = 0;
  
  for(y=0;y<MAP_SIZE;y++)
  {
    for(x=0;x<MAP_SIZE;x++)
    {
      if(map[y][x]>1)
      {
        cnt++;
      }
    }
  }

  printf("Count: %i\n",cnt);
  return 0;
}
