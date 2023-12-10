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
int path[200][200];
int possible[200][200];
int maxsteps = 0;
char newmap[200][200];

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

void printpath(void)
{
  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      if(path[y][x] == -1)
      {
        if(possible[y][x])
        {
          printf("P");
        }
        else
        {
          printf(" ");
        }
      }
      else
      {
        if(path[y][x]==maxsteps)
        {
                    printf("E");
          //          printf("%c",data[y][x]);
        }
        else
        {
          printf("%c",data[y][x]);
        }
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
    memcpy(path,visited,sizeof(visited));
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

  if(steps==maxsteps)
  {
    memcpy(path,visited,sizeof(visited));
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

void fillp(int y,int x)
{
  newmap[y][x]='P';
  
  if(x && (newmap[y][x-1]=='.'))
  {
    fillp(y,x-1);
  }
  if(((x+1)<maxx) && (newmap[y][x+1]=='.'))
  {
    fillp(y,x+1);
  }
  if(y && (newmap[y-1][x]=='.'))
  {
    fillp(y-1,x);
  }
  if(((y+1)<maxy) && (newmap[y+1][x]=='.'))
  {
    fillp(y+1,x);
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

  {
    memset(newmap,'.',sizeof(newmap));
    for(int y=0;y<maxy;y++)
    {
      for(int x=0;x<maxx;x++)
      {
        if(path[y][x]!=-1)
        {
          newmap[y][x] = data[y][x];
        }
      }
    }
  }
  

  {
    // Walk the new path color to the right
    int y = sposy;
    int x = sposx;
    int dir = 8;  // left = 8, down = 4, right = 2, up = 1  lmf on the startvalue...
      
    do
    {
      switch(dir)
      {
        case 1:  //up
          if(x && (newmap[y][x-1]=='.'))
          {
            newmap[y][x-1]='P';
          }
          y--;
          if(x && (newmap[y][x-1]=='.'))  // Missing 5 if we don't also look after move before changing direction.
          {
            newmap[y][x-1]='P';
          }
          break;
        case 2: //right
          if(y && newmap[y-1][x]=='.')
          {
            newmap[y-1][x]='P';
          }
          x++;
          if(y && newmap[y-1][x]=='.')
          {
            newmap[y-1][x]='P';
          }
          break;
        case 4: //down
          if(((x+1)<maxx) && newmap[y][x+1]=='.')
          {
            newmap[y][x+1]='P';
          }
          y++;
          if(((x+1)<maxx) && newmap[y][x+1]=='.')
          {
            newmap[y][x+1]='P';
          }
          break;
        case 8: //left
          if(((y+1)<maxy) && newmap[y+1][x]=='.')
          {
            newmap[y+1][x]='P';
          }
          x--;
          if(((y+1)<maxy) && newmap[y+1][x]=='.')
          {
            newmap[y+1][x]='P';
          }
          break;
      }
      switch(newmap[y][x])
      {
        case '|':
        case '-':
          // Same direction...
          break;
        case 'F':
          if(dir == 1)
          {
            dir = 2;
          }
          else if (dir == 8)
          {
            dir = 4;
          }
          else
          {
            printf("Oops! %i:%i dir %i\n",y,x,dir);
            exit(-1);
          }
          break;
        case 'J':
          if(dir == 4)
          {
            dir = 8;
          }
          else if (dir == 2)
          {
            dir = 1;
          }
          else
          {
            printf("Oops! %i:%i dir %i\n",y,x,dir);
            exit(-1);
          }
          break;
        case 'L': // left = 8, down = 4, right = 2, up = 1
          if(dir == 4)
          {
            dir = 2;
          }
          else if (dir == 8)
          {
            dir = 1;
          }
          else
          {
            printf("Oops! %i:%i dir %i\n",y,x,dir);
            exit(-1);
          }
          break;
        case '7':
        case 'S':
          if(dir == 2)
          {
            dir = 4;
          }
          else if (dir == 1)
          {
            dir = 8;
          }
          else
          {
            printf("Oops! %i:%i dir %i\n",y,x,dir);
            exit(-1);
          }
          break;
        default:
          printf("Oops! %i:%i dir %i map %c\n",y,x,dir,newmap[y][x]);
          exit(-1);
          break;
      }
    }
    while(newmap[y][x]!='S');
    
    for(int y=0;y<maxy;y++)
    {
      for(int x=0;x<maxx;x++)
      {
        if(newmap[y][x]=='P')
        {
          fillp(y,x);
        }
      }
    }

    {
      int cnt = 0;
      
      for(int y=0;y<maxy;y++)
      {
        for(int x=0;x<maxx;x++)
        {
          if(newmap[y][x]=='P')
          {
            cnt++;
          }
          //printf("%c",newmap[y][x]);
        }
        //printf("\n");
      }
      printf("Cnt: %i\n",cnt);
    }
  }
  
  return 0;
}

