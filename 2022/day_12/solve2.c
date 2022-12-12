#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data_in[] = {
#include "data.txt"
};

int sy = -1;
int sx = -1;
int ey = -1;
int ex = -1;
int my = -1;
int mx = -1;
int cnt = 0;

int vismap[41][161];
char data[41][161];

typedef struct {
  int y;
  int x;
} queue_t;

#define QLEN (41*161)
queue_t* now_p = NULL;
queue_t* next_p = NULL;

int main(int argc, char* argv[])
{
  my = sizeof(data_in)/sizeof(data_in[0]);
  mx = strlen(data_in[0]);

  memset(vismap,0,sizeof(vismap));
  memset(data,0,sizeof(data));

  for(int y=0;y<my;y++)
  {
    for(int x=0;x<mx;x++)
    {
      data[y][x] = data_in[y][x];
      if('S' == data[y][x])
      {
        sy = y;
        sx = x;
      }
      if('E' == data[y][x])
      {
        ey = y;
        ex = x;
      }
      
    }
  }

  now_p = malloc(sizeof(queue_t)*QLEN);
  next_p = malloc(sizeof(queue_t)*QLEN);
  memset(now_p,-1,sizeof(queue_t)*QLEN);
  memset(next_p,-1,sizeof(queue_t)*QLEN);
  int next_idx=0;
  int now_idx=0;
  
  now_p[now_idx].y=ey;
  now_p[now_idx].x=ex;
  data[ey][ex]='z';  // E has elevation z
  data[sy][sx]='a';  // S has elevation a
  vismap[ey][ex] = 1; // This is visited!

  while(1)
  {
    while((now_p[now_idx].y)>=0)
    {
      int y = now_p[now_idx].y;
      int x = now_p[now_idx].x;
      
      if(data[y][x] == 'a')
      {
        printf("Found path at len: %i\n",cnt);
        return 0;
      }
      //Queue all possible
      // Left?
      if(x && ((data[y][x-1] - data[y][x]) > -2) && !vismap[y][x-1])
      {
        vismap[y][x-1] = 1;
        next_p[next_idx].y = y;
        next_p[next_idx].x = x-1;
        next_idx++;
      }
      
      // Right?
      if(((x+1)<mx) && ((data[y][x+1] - data[y][x]) > -2)  && !vismap[y][x+1])
      {
        vismap[y][x+1] = 1;
        next_p[next_idx].y = y;
        next_p[next_idx].x = x+1;
        next_idx++;
      }
      
      // Up?
      if(y && ((data[y-1][x] - data[y][x]) > -2)  && !vismap[y-1][x])
      {
        vismap[y-1][x] = 1;
        next_p[next_idx].y = y-1;
        next_p[next_idx].x = x;
        next_idx++;
      }

      // Down?
      if(((y+1)<my) && ((data[y+1][x] - data[y][x]) > -2)  && !vismap[y+1][x])
      {
        vismap[y+1][x] = 1;
        next_p[next_idx].y = y+1;
        next_p[next_idx].x = x;
        next_idx++;
      }

      now_idx++;
    }

    // Next level
    cnt++;
    free(now_p);
    now_p = next_p;
    
    next_p = malloc(sizeof(queue_t)*QLEN);
    memset(next_p,-1,sizeof(queue_t)*QLEN);
    next_idx=0;
    now_idx=0;
  }

  return 0;
}
