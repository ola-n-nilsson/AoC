#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef enum
{
  NORTH = 0,
  EAST,
  SOUTH,
  WEST
} dir_t;

char* data[] = {
#include "data.txt"
};
int maxy;
int maxx;

typedef struct head {
  int y;
  int x;
  dir_t dir;
  int steps;
  int acc;
  unsigned int h;
  void* next_p;
} head_t;

head_t* open;

int history[150][150][4][4];

void addOpen(int yy, int xx, dir_t dir,int steps,int acc, unsigned int h)
{
  head_t* search = open;
  head_t* last = NULL;
  head_t* new;
  
  while(search && (search->h<h))
  {
    last = search;
    search = search->next_p;
  }

  new = malloc(sizeof(head_t));
  new->y = yy;
  new->x = xx;
  new->dir = dir;
  new->steps = steps;
  new->acc = acc;
  new->h = h;
  new->next_p=NULL;
  if(last)
  {
    last->next_p = new;
    new->next_p = search;
  }
  else
  {
    new->next_p = open;
    open = new;
  }
}


head_t* getnode(void)
{
  head_t* ret = open;
  if(open)
  {
    open = ret->next_p;
  }
  return ret;
}


int asearch(void)
{
  head_t* current;
  int y;
  int x;
  dir_t dir;
  int steps;
  int acc;
  int yy;
  int xx;
  unsigned int h;
  
  if(!open)
  {
    printf("Open empty...\n");
    exit(-1);
  }

  current = getnode();
  y = current->y;
  x = current->x;
  dir = current->dir;
  steps = current->steps;
  acc = current->acc;
  h = current->h;
  
  if(history[y][x][dir][steps])
  {
    free(current);
    return 0;
  }
  history[y][x][dir][steps] = 1;

  if(current && (y==(maxy-1)) && (x==(maxx-1)))
  {
    printf("Done, accumulated %i\n",acc);
    free(current);
    return 1;
  }

  yy = y;
  xx = x;
  switch(dir)
  {
    case NORTH:
      yy--;
      break;
    case EAST:
      xx++;
      break;
    case SOUTH:
      yy++;
      break;
    case WEST:
      xx--;
      break;
  }
  if((xx>=0) && (xx<maxx) && (yy>=0) && (yy<maxy))
  {
    acc+=data[yy][xx]-'0';
    h = (maxy-1-yy) + (maxx-1-xx) + acc;
    // Left and Right
    switch(dir)
    {
      case NORTH:
      case SOUTH:
        addOpen(yy,xx,WEST,1,acc,h);
        addOpen(yy,xx,EAST,1,acc,h);
        break;
      case EAST:
      case WEST:
        addOpen(yy,xx,NORTH,1,acc,h);
        addOpen(yy,xx,SOUTH,1,acc,h);
        break;
    }
    // Ahead
    if(steps<3)
    {
      addOpen(yy,xx,dir,steps+1,acc,h);
    }
  }
  free(current);
  return 0;
}


int main(int argc, char* argv[])
{
  head_t* start = malloc(sizeof(head_t));
  maxy = sizeof(data)/sizeof(data[0]);
  maxx = strlen(data[0]);
  printf("Field size %i:%i\n",maxy,maxx);
  int done = 0;

  memset(history,0,sizeof(history));
  
  start->y = 0;
  start->x = 0;
  start->dir = EAST;
  start->steps = 1;
  start->next_p = NULL;
  start->acc = 0;
  start->h = (maxy-1)+(maxx-1);
  open = start;

  start = malloc(sizeof(head_t));
  start->y = 0;
  start->x = 0;
  start->dir = SOUTH;
  start->steps = 1;
  start->next_p = NULL;
  start->acc = 0;
  start->h = (maxy-1)+(maxx-1);
  open->next_p = start;
  
  do
  {
    done = asearch();
  } while(!done);

  return 0;
}

