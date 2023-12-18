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
  int distance;
  int acc;
  void* next_p;
} head_t;

head_t* open;
head_t* from = NULL;

unsigned long gScore[150][150][4][16];
unsigned long fScore[150][150][4][16];
head_t cameFrom[150][150][4][16];
char path[150][150];

unsigned long h(int y, int x)
{
  return 0;
  //  return ((maxy-y) + (maxx-x))*10;  // Wikipedia say h(n) = 0 gives Djinkstra. Let's try that...
}

unsigned long reconstruct(head_t* c)
{
  unsigned long sum = 0;

  while(c->y || c->x)
  {
    printf("Path %i:%i %i\n",c->y,c->x,data[c->y][c->x] - '0');
    switch(c->dir)
    {
      case NORTH:
        path[c->y][c->x] = '^';
        break;
      case EAST:
        path[c->y][c->x] = '>';
        break;
      case SOUTH:
        path[c->y][c->x] = 'v';
        break;
      case WEST:
        path[c->y][c->x] = '<';
        break;
    }
    sum += data[c->y][c->x] - '0';
    c = &cameFrom[c->y][c->x][c->dir][c->steps];
  }
  return sum;
}

void addOpen(head_t* c, int yy, int xx, dir_t dir,int steps,int acc)
{
  unsigned long tgs;
  head_t* search = open;
  head_t* last = NULL;
  
  tgs = gScore[c->y][c->x][c->dir][c->steps] + (data[yy][xx] - '0');
  if(tgs < gScore[yy][xx][dir][steps])
  {
    memcpy(&cameFrom[yy][xx][dir][steps],c,sizeof(head_t));
    gScore[yy][xx][dir][steps] = tgs;
    fScore[yy][xx][dir][steps] = tgs+h(yy,xx);

    while(search)
    {
      if(search->y==yy && search->x==xx && search->dir==dir && search->steps==steps)
      {
        //Already in open
        return;
      }
      last = search;
      search = search->next_p;
    }
    if(!search)
    {
      search = malloc(sizeof(head_t));
      search->y = yy;
      search->x = xx;
      search->dir = dir;
      search->steps = steps;
      search->acc = acc;
      search->next_p=NULL;
      if(last)
      {
        last->next_p = search;
      }
      else
      {
        open = search;
      }
    }
  }
}

head_t* getnode(void)
{
  head_t* search = open;
  head_t* last = NULL;
  head_t* lowest = NULL;
  head_t* beforelowest = NULL;
  unsigned long low = (unsigned long)-1;
  
  if(!open)
  {
    return NULL;
  }
  while(search)
  {
    unsigned long fs = fScore[search->y][search->x][search->dir][search->steps];
    
    if(fs < low)
    {
      low = fs;
      lowest = search;
      beforelowest = last;
    }
    last = search;
    search = search->next_p;
  }
  if(beforelowest)
  {
    beforelowest->next_p = lowest->next_p;
  }
  else
  {
    open = lowest->next_p;
  }
  lowest->next_p = NULL;

  return lowest;
}

int asearch(void)
{
  head_t* current;
  int y;
  int x;
  dir_t dir;
  int steps;
  int acc;
  
  if(!open)
  {
    printf("Open empty...\n");
    exit(-1);
  }
  current = getnode();
  
  if(current && (current->y==(maxy-1)) && (current->x==(maxx-1)) && (current->steps>=3))
  {
    printf("Done, accumulated %i\n",current->acc);
    printf("Done, distance %lu\n",reconstruct(current));
    return 1;
  }

  y = current->y;
  x = current->x;
  dir = current->dir;
  steps = current->steps;
  acc = current->acc;
  
  // Continue ahead?
  if(steps<9)
  {
    switch(dir)
    {
      case NORTH:
        if(y)
        {
          addOpen(current, y-1,x,dir,steps+1,acc+data[y-1][x]-'0');
        }
        break;
      case EAST:
        if(x<(maxx-1))
        {
          addOpen(current, y,x+1,dir,steps+1,acc+data[y][x+1]-'0');
        }
        break;
      case SOUTH:
        if(y<(maxy-1))
        {
          addOpen(current, y+1,x,dir,steps+1,acc+data[y+1][x]-'0');
        }
        break;
      case WEST:
        if(x)
        {
          addOpen(current, y,x-1,dir,steps+1,acc+data[y][x-1]-'0');
        }
        break;
    }
  }
  // Turn left?
  if(steps>=3)
  {
    switch(dir)
    {
      case NORTH:
        if(x)
        {
          addOpen(current, y,x-1,WEST,0,acc+data[y][x-1]-'0');
        }
        break;
      case EAST:
        if(y)
        {
          addOpen(current, y-1,x,NORTH,0,acc+data[y-1][x]-'0');
        }
        break;
      case SOUTH:
        if(x<(maxx-1))
        {
          addOpen(current, y,x+1,EAST,0,acc+data[y][x+1]-'0');
        }
        break;
      case WEST:
        if(y<(maxy-1))
        {
          addOpen(current, y+1,x,SOUTH,0,acc+data[y+1][x]-'0');
        }
        break;
    }
    // Turn right?
    switch(dir)
    {
      case NORTH:
        if(x<(maxx-1))
        {
          addOpen(current, y,x+1,EAST,0,acc+data[y][x+1]-'0');
        }
        break;
      case EAST:
        if(y<(maxy-1))
        {
          addOpen(current, y+1,x,SOUTH,0,acc+data[y+1][x]-'0');
        }
        break;
      case SOUTH:
        if(x)
        {
          addOpen(current, y,x-1,WEST,0,acc+data[y][x-1]-'0');
        }
        break;
      case WEST:
        if(y)
        {
          addOpen(current, y-1,x,NORTH,0,acc+data[y-1][x]-'0');
        }
        break;
    }
  }
  return 0;
}

int main(int argc, char* argv[])
{
  head_t* start = malloc(sizeof(head_t));
  maxy = sizeof(data)/sizeof(data[0]);
  maxx = strlen(data[0]);
  printf("Field size %i:%i\n",maxy,maxx);
  int done = 0;

  memset(gScore,-1,sizeof(gScore));
  memset(fScore,-1,sizeof(fScore));
  memset(cameFrom,0,sizeof(cameFrom));

  fScore[0][0][EAST][0] = h(0,0); 
  gScore[0][0][EAST][0] = 0;
  
  start->y = 0;
  start->x = 0;
  start->dir = EAST;
  start->steps = 0;
  start->next_p = NULL;
  start->acc = 0;
  open = start;

  memset(path,0,sizeof(path));
  
  do
  {
    done = asearch();
  } while(!done);

  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      if(path[y][x])
      {
        printf("%c",path[y][x]);
      }
      else
      {
        printf("%c",data[y][x]);
      }
        
    }
    printf("\n");
  }
  
  
  return 0;
}

