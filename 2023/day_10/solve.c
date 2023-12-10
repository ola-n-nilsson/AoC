#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};
int maxy;
int maxx;
int sposy;
int sposx;
int visited[200][200];
int maxsteps = 0;

int ispipe(char c)
{
  switch(c)
  {
    case '|':
    case '-':
    case 'L':
    case 'J':
    case '7':
    case 'F':
      return 1;
  }
  return 0;
}

int isnorth(char c)
{
  switch(c)
  {
    case '|':
      //    case '-':
    case 'L':
    case 'J':
      //    case '7':
      //    case 'F':
    case 'S':
      return 1;
  }
  return 0;
}

int iseast(char c)
{
  switch(c)
  {
    //    case '|':
    case '-':
    case 'L':
      //    case 'J':
      //    case '7':
    case 'F':
    case 'S':
      return 1;
  }
  return 0;
}

int issouth(char c)
{
  switch(c)
  {
    case '|':
      //    case '-':
      //    case 'L':
      //    case 'J':
    case '7':
    case 'F':
    case 'S':
      return 1;
  }
  return 0;
}

int iswest(char c)
{
  switch(c)
  {
    //    case '|':
    case '-':
      //    case 'L':
    case 'J':
    case '7':
      //    case 'F':
    case 'S':
      return 1;
  }
  return 0;
}

void printvis(void)
{
  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      if(visited[y][x] == -1)
      {
        printf(" .  ");
      }
      else
      {
        printf("%03i ",visited[y][x]);
      }
    }
    printf("\n");
  }
}

void step2(int y1,int x1, int y2, int x2, int steps);

void step1(int y1,int x1, int y2, int x2, int steps)
{
  int pos1 = 0;
  
  steps++;
  if(steps>maxsteps)
  {
    maxsteps = steps;
  }
  // First 1
  if(y1 && isnorth(data[y1][x1]) && ispipe(data[y1-1][x1]) && (visited[y1-1][x1]==-1)) // look up
  {
    // 1 can go up
    pos1 |= 1;
  }
  if(((x1+1)<maxx) && iseast(data[y1][x1]) && ispipe(data[y1][x1+1]) && (visited[y1][x1+1]==-1))  // right
  {
    // 1 can go right
    pos1 |= 2;
  }
  if(((y1+1)<maxy) && issouth(data[y1][x1]) && ispipe(data[y1+1][x1]) && (visited[y1+1][x1]==-1))  // down
  {
    // 1 can go down
    pos1 |= 4;
  }
  if(x1 && iswest(data[y1][x1]) && ispipe(data[y1][x1-1]) && (visited[y1][x1-1]==-1))  // left
  {
    // 1 can go left
    pos1 |= 8;
  }
      
  for(int dir1=1;dir1<16;dir1=dir1<<1)
  {
    if(pos1&dir1)
    {
      switch(dir1)
      {
        case 1:  // 1 goes up
          visited[y1-1][x1] = steps;
          step2(y1-1,x1,y2,x2,steps);
          visited[y1-1][x1] = -1;
          break;
        case 2:  // 1 goes right
          visited[y1][x1+1] = steps;
          step2(y1,x1+1,y2,x2,steps);
          visited[y1][x1+1] = -1;
          break;
        case 4:  // 1 goes down
          visited[y1+1][x1] = steps;
          step2(y1+1,x1,y2,x2,steps);
          visited[y1+1][x1] = -1;
          break;
        case 8:  // 1 goes left 
          visited[y1][x1-1] = steps;
          step2(y1,x1-1,y2,x2,steps);
          visited[y1][x1-1] = -1;
          break;
      }
    }
  }

}


void step2(int y1,int x1, int y2, int x2, int steps)
{
  int pos2 = 0;
  
  // 2
  if(x2 && iswest(data[y2][x2]) && ispipe(data[y2][x2-1]) && (visited[y2][x2-1]==-1))  // left
  {
    // 2 can go left
    pos2 |= 8;
  }
  if(((y2+1)<maxy) && issouth(data[y2][x2]) && ispipe(data[y2+1][x2]) && (visited[y2+1][x2]==-1))  // down
  {
    // 2 can go down
    pos2 |= 4;
  }
  if(((x2+1)<maxx) && iseast(data[y2][x2]) && ispipe(data[y2][x2+1]) && (visited[y2][x2+1]==-1))  // right
  {
    // 2 can go right
    pos2 |= 2;
  }
  if(y2 && isnorth(data[y2][x2]) && ispipe(data[y2-1][x2]) && (visited[y2-1][x2]==-1)) // look up
  {
    // 2 can go up
    pos2 |= 1;
  }

  for(int dir2=1;dir2<16;dir2=dir2<<1)
  {
    if(pos2&dir2)
    {
      switch(dir2)
      {
        case 1:  // 2 goes up
          visited[y2-1][x2] = steps;
          step1(y1,x1,y2-1,x2,steps);
          visited[y2-1][x2] = -1;
          break;
        case 2:  // 2 goes right
          visited[y2][x2+1] = steps;
          step1(y1,x1,y2,x2+1,steps);
          visited[y2][x2+1] = -1;
          break;
        case 4:  // 2 goes down
          visited[y2+1][x2] = steps;
          step1(y1,x1,y2+1,x2,steps);
          visited[y2+1][x2] = -1;
          break;
        case 8:  // 2 goes left 
          visited[y2][x2-1] = steps;
          step1(y1,x1,y2,x2-1,steps);
          visited[y2][x2-1] = -1;
          break;
      }
    }
  }

}


int main(int argc, char* argv[])
{
  maxy = sizeof(data)/sizeof(data[0]);
  maxx = strlen(data[0]);

  memset(visited,-1,sizeof(visited));
  
  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      if(data[y][x]=='S')
      {
        sposy = y;
        sposx = x;
      }
    }
  }
  printf("Size %i:%i S pos %i:%i\n",maxy,maxx,sposy,sposx);

  {
    int y1 = sposy;
    int x1 = sposx;
    int y2 = sposy;
    int x2 = sposx;
    int steps = 0;
    
    visited[y2][x2] = steps;
    step1(y1,x1,y2,x2,steps);
  }
  printf("Max steps: %i\n",maxsteps);
  return 0;
}

