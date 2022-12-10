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
    else
    {
      int starty,stopy;
      int startx,stopx, stepx;

      if(lines[i][1] > lines[i][3])
      {
        starty = lines[i][3];
        stopy = lines[i][1];
        startx = lines[i][2];
        stopx = lines[i][0];
        if(stopx<startx)
        {
          printf("1 ola: line %i goes backwards in x\n",i);
          stepx = -1;
        }
        else
        {
          printf("2 ola: line %i \n",i);
          stepx = 1;
        }
      }
      else
      {
        starty = lines[i][1];
        stopy = lines[i][3];
        startx = lines[i][0];
        stopx = lines[i][2];
        if(stopx<startx)
        {
          printf("3 ola: line %i goes backwards in x\n",i);
          stepx = -1;
        }
        else
        {
          printf("4 ola: line %i \n",i);
          stepx = 1;
        }
      }

      x=startx;
      for(y=starty;y<=stopy;y++,x+=stepx)
      {
        //        printf("ola: coloring %i,%i for line %i\n",y,x,i);
        map[y][x] += 1;
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
