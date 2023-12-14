#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

char field[200][200];
int maxy;
int maxx;

int main(int argc, char* argv[])
{
  maxy = sizeof(data)/sizeof(data[0]);
  maxx = strlen(data[0]);
  int move = 1;
  
  printf("Max %i:%i\n",maxy,maxx);
  for(int y=0;y<maxy;y++)
  {
    strcpy(field[y],data[y]);
  }

  while(move)
  {
    move = 0;
    for(int y=0;y<maxy;y++)
    {
      for(int x=0;x<maxx;x++)
      {
        if(field[y][x]=='O')
        {
          if(y && field[y-1][x] == '.')
          {
            field[y-1][x] = 'O';
            field[y][x] = '.';  //Always . below O
            move=1;
          }
        }
      }
    }
  }

  {
    unsigned long load = 0;
    for(int y=0;y<maxy;y++)
    {
      for(int x=0;x<maxx;x++)
      {
        printf("%c",field[y][x]);
        if(field[y][x]=='O')
        {
          load += (maxy-y);
        }
      }
      printf("\n");
    }
    printf("\nLoad: %lu\n",load);
  }

  
  return 0;
}
