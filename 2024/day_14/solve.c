#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

const long data[] = {
#include "data.txt"
};

int field[200][200];
int fielda[200][200];

int main(int argc, char* argv[])
{
  long maxx=data[0];
  long maxy=data[1];
  long qx = maxx/2; // less than and more than
  long qy = maxy/2; // less than and more than
  long cnt[4] = {0,0,0,0};
  
  printf("Counting for a plane %li:%li, y divider %li, x divider %li\n",maxy,maxx,qy,qx);
  memset(field,0,sizeof(field));
  memset(fielda,0,sizeof(fielda));
  for(int i=4;i<(sizeof(data)/sizeof(data[0]));i+=4)
  {
    long px = data[i];
    long py = data[i+1];
    long vx = data[i+2];
    long vy = data[i+3];

    printf("Robot %i (%li:%li:%li:%li): ",i/4,py,px,vy,vx);
    field[py][px]++;
    for(int j=0;j<100;j++)
    {
      px+=vx;
      py+=vy;
      while(px<0)
      {
        px+=maxx;
      }
      while(py<0)
      {
        py+=maxy;
      }
      while(px>=maxx)
      {
        px-=maxx;
      }
      while(py>=maxy)
      {
        py-=maxy;
      }
    }
    (fielda[py][px])++;
    printf("at %li:%li\n",py,px);
    
    if((py<qy) && (px<qx))
    {
      cnt[0]++;
    } else if((py<qy) && (px>qx))
    {
      cnt[1]++;
    } else if((py>qy) && (px<qx))
    {
      cnt[2]++;
    } else if((py>qy) && (px>qx))
    {
      cnt[3]++;
    }
  }

  printf("Q1: %li Q2: %li Q3: %li Q4: %li Mul: %li\n",cnt[0],cnt[1],cnt[2],cnt[3],cnt[0]*cnt[1]*cnt[2]*cnt[3]);

  printf("Before:\n");
  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      printf("%c",field[y][x]?'0'+field[y][x]:'.');
    }
    printf("\n");
  }
  printf("After:\n");
  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      printf("%c",fielda[y][x]?'0'+fielda[y][x]:'.');
    }
    printf("\n");
  }
  return 0;
}
