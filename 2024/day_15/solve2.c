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

int field[200][400];
int maxy;
int maxx;
int py;
int px;
#define STONE (3)
#define BOXL (1)
#define BOXR (2)

typedef struct move_t
{
  int y;
  int x;
} move_t;

move_t moves[200*200];
int midx = 0;

void insertmove(int y,int x)
{
  for(int i=0;i<midx;i++)
  {
    if(moves[i].y == y && moves[i].x == x)
    {
      return;
    }
  }
  moves[midx].y = y;
  moves[midx].x = x;
  midx++;
  return;
}

int recadd(int y,int x, int dy)
{
  int ny = y+dy;
  
  if(field[ny][x]!=STONE && field[ny][x+1]!=STONE)
  {
    //This can possibly move
    insertmove(y,x);
    if(field[ny][x]==BOXL)
    {
      // One exactly on top of us
      return recadd(ny,x,dy);
    }
    else if(field[ny][x]==BOXR)
    {
      // One to our left
      if(!recadd(ny,x-1,dy))
      {
        return 0; // This side wont move.
      }
    }
    if(field[ny][x+1]==BOXL)
    {
      //And one to our right
      if(!recadd(ny,x+1,dy))
      {
        return 0; // This side wont move.
      }
    }
    return 1;
  }
  else
  {
    return 0;
  }
}

int compareup(const void* a, const void* b)
{
  move_t* am= (move_t*)a;
  move_t* bm= (move_t*)b;

  if(am->y==bm->y)
  {
   return (am->x - bm->x);
  }
  else
  {
   return (am->y - bm->y);
  }
}

int comparedown(const void* a, const void* b)
{
  move_t* am= (move_t*)a;
  move_t* bm= (move_t*)b;

  if(am->y==bm->y)
  {
   return (am->x - bm->x);
  }
  else
  {
   return (bm->y - am->y);
  }
}


void moveb(int dy)
{
  int y = py+dy;
  int x = px;
  
  if(field[y][x]==BOXR)
  {
    x--;
  }
  midx = 0;
  if(recadd(y,x,dy))
  {
    //printf("Will move %i boxes\n",midx);
    if(dy>0)
    {
      qsort(moves, midx, sizeof(move_t), comparedown);
    }
    else
    {
      qsort(moves, midx, sizeof(move_t), compareup);
    }
    for(int i=0;i<midx;i++)
    {
      int yy = moves[i].y;
      int xx = moves[i].x;

      field[yy+dy][xx] = BOXL;
      field[yy+dy][xx+1] = BOXR;
      field[yy][xx] = 0;
      field[yy][xx+1] = 0;
    }
    // And move robot
    py+=dy;
  }
  else
  {
    //    printf("Will not move boxes\n");
  }
}

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

  if(dy)
  {
    if(!field[py+dy][px])
    {
      //Empty, just move.
      py+=dy;
      return;
    }
    else if(field[py+dy][px]==STONE)
    {
      return;
    }
    moveb(dy); // The new and challenging move.
    return;
  }
  
  do
  {
    ny += dy;
    nx += dx;
  } while(field[ny][nx]!=STONE && (field[ny][nx]==BOXL || field[ny][nx]==BOXR));

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
    for(int x=0;x<(2*maxx);x++)
    {
      int putl = 0;
      int putr = 0;

      switch(data[y][x])
      {
        case '@':
          py=y;
          px=2*x;
          break;
        case '#':
          putl = STONE;
          putr = STONE;
          break;
        case 'O':
          putl = BOXL;
          putr = BOXR;
          break;
      }
      field[y][2*x] = putl;
      field[y][(2*x)+1] = putr;
    }
  }

  printf("Field %i:%i len of mov %i robot %i:%i\n",maxy,maxx,(int)strlen(move),py,px);
  
  while(*p)
  {
    if(*p!='\n')
    {
      movea(*p);
      //printf("Robot at %i:%i after move %c\n",py,px,*p);
      if(!py || !px || (py+1>=maxy) || (px+1>=(2*maxx)))
      {
        printf("Out of bounds!\n");
        exit(-1);



      }

    }
    p++;
  }

  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<(2*maxx);x++)
    {
      if(y==py && x==px)
      {
        printf("@");
      }
      else if(field[y][x]==STONE)
      {
        printf("#");
      }
      else if(field[y][x]==BOXL)
      {
        printf("[");
        distsum += (y*100)+x;
      }
      else if(field[y][x]==BOXR)
      {
        printf("]");
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
