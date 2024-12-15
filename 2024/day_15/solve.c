#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#if 0
char* data[] = {
#include "data2.txt"
};

char* move = {
#include "data2m.txt"
};
#else
char* data[] = {
#include "data.txt"
};

char* move = {
#include "datam.txt"
};
#endif

int field[200][200];
int maxy;
int maxx;
int py;
int px;
#define STONE (2)
#define BOX (1)

void movea(char c)
{
  int dy = 0;
  int dx = 0;
  int ny = py;
  int nx = px;
  
  switch(c)
  {
    case '^':
      dy = -1;
      break;
    case '<':
      dx = -1;
      break;
    case '>':
      dx = 1;
      break;
    case 'v':
      dy = 1;
      break;
    default:
      printf("Oops!\n");
      exit(-1);
  }

  do
  {
    ny += dy;
    nx += dx;
  } while(field[ny][nx]!=STONE && field[ny][nx]==BOX);

  // We are at a stone or an empty position
  if(!field[ny][nx])
  {
    // We are moving the robot and any boxes...
    while(ny!=py || nx!=px)
    {
      field[ny][nx] = field[ny-dy][nx-dx];
      ny -= dy;
      nx -= dx;
    }
    py += dy;
    px += dx;
  }
}

int main(int argc, char* argv[])
{
  char* p = move;
  unsigned long distsum = 0;
    
  maxy = sizeof(data)/sizeof(data[0]);
  maxx = strlen(data[0]);

  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      int put = 0;

      switch(data[y][x])
      {
        case '@':
          py=y;
          px=x;
          break;
        case '#':
          put = STONE;
          break;
        case 'O':
          put = BOX;
          break;
      }
      field[y][x] = put;
    }
  }

  printf("Field %i:%i len of mov %i robot %i:%i\n",maxy,maxx,(int)strlen(move),py,px);
  
  while(*p)
  {
    if(*p!='\n')
    {
      movea(*p);
    }
    p++;
  }

  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      if(y==py && x==px)
      {
        printf("@");
      }
      else if(field[y][x]==STONE)
      {
        printf("#");
      }
      else if(field[y][x]==BOX)
      {
        printf("O");
        distsum += (y*100)+x;
      }
      else
      {
        printf(".");
      }
    }
    printf("\n");
  }
  printf("Distsum: %lu\n",distsum);
  return 0;
}
