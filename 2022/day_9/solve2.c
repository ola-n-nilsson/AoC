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

void PrintVisited(void)
{
  for(int y=280;y<320;y++)
  {
    for(int x=280;x<320;x++)
    {
      //      printf("%c",visited[y][x]?'#':'.');
    }
    //    printf("\n");
  }
}

int main(int argc, char* argv[])
{
  int x=300; //Start pos for H
  int y=300; //Start pos for H
  int t_x[10];
  int t_y[10];

  memset(visited,0,sizeof(visited));
  visited[y][x] = '#';

  for(int i=0;i<10;i++)
  {
    t_x[i]=300;
    t_y[i]=300;
  }
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
    t_x[0]=x;
    t_y[0]=y;
    int move=1;

    while(move)
    {
      move = 0;
      for(int i=1;i<10;i++)
      {
        if((abs(t_x[i-1]-t_x[i])>1) && abs(t_y[i-1]-t_y[i])<=1)
        {
          //we will move t_x[i-1], if t_y[i-1] is not right move one step!
          if((t_y[i-1]-t_y[i])>0)
          {
            t_y[i]++;
            move++;
          }
          if((t_y[i-1]-t_y[i])<0)
          {
            t_y[i]--;
            move++;
          }
        }
        if((abs(t_y[i-1]-t_y[i])>1) && abs(t_x[i-1]-t_x[i])<=1)
        {
          //we will move t_y[i-1], if t_x[i-1] is not right move one step!
          if((t_x[i-1]-t_x[i])>0)
          {
            t_x[i]++;
            move++;
          }
          if((t_x[i-1]-t_x[i])<0)
          {
            t_x[i]--;
            move++;
          }
        }
        // Normal move
        if((t_x[i-1]-t_x[i])>1)
        {
          t_x[i]++;
          move++;
        }
        if((t_x[i-1]-t_x[i])<-1)
        {
          t_x[i]--;
          move++;
        }
        if((t_y[i-1]-t_y[i])>1)
        {
          t_y[i]++;
          move++;
        }
        if((t_y[i-1]-t_y[i])<-1)
        {
          t_y[i]--;
          move++;
        }
        printf("%i visited: %i:%i\n",i,t_y[i],t_x[i]);
        if(i==9)
        {
          visited[t_y[i]][t_x[i]] = '#';
        }
      }
    }
    for(int j=0;j<10;j++)
    {
      printf("t_y[%i]:t_x[%i]: %i:%i\n",j,j,t_y[j],t_x[j]);
    }
    PrintVisited();
  }


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
