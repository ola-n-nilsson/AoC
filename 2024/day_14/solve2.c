#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

const long data[] = {
#include "data.txt"
};

int fielda[200][200];

int main(int argc, char* argv[])
{
  long maxx=data[0];
  long maxy=data[1];
  
  for(int k=1;k<10000;k++)
  {
    memset(fielda,0,sizeof(fielda));
    for(int i=4;i<(sizeof(data)/sizeof(data[0]));i+=4)
    {
      long px = data[i];
      long py = data[i+1];
      long vx = data[i+2];
      long vy = data[i+3];

      for(int j=0;j<k;j++)
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
    }

    printf("After %i:\n",k);
    for(int y=0;y<maxy;y++)
    {
      for(int x=0;x<maxx;x++)
      {
        printf("%c",fielda[y][x]?'0'+fielda[y][x]:'.');
      }
      printf("\n");
    }
  }
  return 0;
}
