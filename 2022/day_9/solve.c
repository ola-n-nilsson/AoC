#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>



typedef enum {
  UP,
  DOWN,
  LEFT,
  RIGHT
} op_t;

typedef struct {
  op_t op;
  int step;
} move_t;

const move_t data[] = {
#include "data.txt"
};

char visited[500][500];

int main(int argc, char* argv[])
{
  int x=300; //Start pos for H
  int y=300; //Start pos for H
  int t_x=300;
  int t_y=300;
  int max_x = 0;
  int max_y = 0;
  int min_x = 0;
  int min_y = 0;

  memset(visited,0,sizeof(visited));
  visited[t_y][t_x] = '#';
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    switch(data[i].op)
    {
      case UP:
        printf("%i:%i U %i\n",y,x,data[i].step);
        y-=data[i].step;
        break;
      case DOWN:
        printf("%i:%i D %i\n",y,x,data[i].step);
        y+=data[i].step;
        break;
      case LEFT:
        printf("%i:%i L %i\n",y,x,data[i].step);
        x-=data[i].step;
        break;
      case RIGHT:
        printf("%i:%i R %i\n",y,x,data[i].step);
        x+=data[i].step;
        break;
      default:
        printf("oops!\n");
        exit(-1);
    }
    // Move the T until close to H
    while(abs(x-t_x)>1 || abs(y-t_y)>1)
    {
      if(abs(x-t_x)>1)
      {
        //we will move x, if y is not right move one step!
        if((y-t_y)>0)
        {
          t_y++;
        }
        if((y-t_y)<0)
        {
          t_y--;
        }
      }
      if(abs(y-t_y)>1)
      {
        //we will move y, if x is not right move one step!
        if((x-t_x)>0)
        {
          t_x++;
        }
        if((x-t_x)<0)
        {
          t_x--;
        }
      }
      // Normal move
      if((x-t_x)>1)
      {
        t_x++;
      }
      if((x-t_x)<-1)
      {
        t_x--;
      }
      if((y-t_y)>1)
      {
        t_y++;
      }
      if((y-t_y)<-1)
      {
        t_y--;
      }
      printf("Visited: %i:%i\n",t_y,t_x);
      visited[t_y][t_x] = '#';
    }
    if(x>max_x)
    {
      max_x = x;
    }
    if(y>max_y)
    {
      max_y = y;
    }
    if(x<min_x)
    {
      min_x = x;
    }
    if(y<min_y)
    {
      min_y = y;
    }
  }

  printf("Max: %i:%i Min: %i:%i\n",max_y,max_x,min_y,min_x);

  int cnt = 0;
  for(x=0;x<500;x++)
  {
    for(y=0;y<500;y++)
    {
      if(visited[y][x]=='#')
      {
        cnt++;
      }
    }
  }
  printf("Visited: %i\n",cnt);
  return 0;
}
