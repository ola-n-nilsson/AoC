#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
  int x;
  int y;
  int bx;
  int by;
} pair_t;

pair_t data[] = {
#include "data.txt"
};

int maxx = INT_MIN;
int minx = INT_MAX;
int maxy = INT_MIN;
int miny = INT_MAX;

typedef struct
{
  int sx;
  int ex;
} range_t;

range_t ranges[40];
int range_idx;

void buildranges(int ty)
{
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    int y = data[i].y;
    int x = data[i].x;
    int by = data[i].by;
    int bx = data[i].bx;
    int r = 0;

    r=abs(y-by)+abs(x-bx);
    
    //    printf("%i:%i with becon: %i:%i radie: %i ",data[i].y,data[i].x,data[i].by,data[i].bx,r);

    int distty = abs(ty-y);
    if (r>distty)
    {
      int width = (r - distty);
      //printf("Covering at ty: %i to %i",x-width,x+width);
      ranges[range_idx].sx = x-width;
      ranges[range_idx].ex = x+width;
      range_idx++;
    }
  }
}

int main(int argc, char* argv[])
{
  for(int ty=0;ty<=4000000;ty++)
  {
    range_idx = 0;
    buildranges(ty);
    int x=0;
    
    while(x<=4000000)
    {
      int lastx = x;
      
      for(int i=0;i<range_idx;i++)
      {
        if(x>=ranges[i].sx && x<=ranges[i].ex)
        {
          // Skip until end of this matching range.
          x = ranges[i].ex +1;
          break;
        }
      }
      if(x==lastx)
      {
        printf("Possible: %i:%i\n",ty,x);
        printf("Distress: %lu\n",(unsigned long)x*4000000+ty);
        return 0;
      }
    }
  }
  
  return 0;
}
