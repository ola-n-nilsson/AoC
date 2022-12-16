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

int main(int argc, char* argv[])
{
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    int y = data[i].y;
    int x = data[i].x;
    int by = data[i].by;
    int bx = data[i].bx;
    int r = 0;

    r=abs(y-by)+abs(x-bx);
    
    printf("%i:%i with becon: %i:%i radie: %i ",data[i].y,data[i].x,data[i].by,data[i].bx,r);

    int distty = abs(2000000-y);
    if (r>distty)
    {
      int width = (r - distty);
      printf("Covering at ty: %i to %i",x-width,x+width);
    }

    if(by==2000000)
    {
      printf(" beacon at ty...");
    }
    
    printf("\n");
    
    if(y>maxy)
      maxy = y;
    if(x>maxx)
      maxx = x;
    if(y<miny)
      miny = y;
    if(x<minx)
      minx = x;
    if(by>maxy)
      maxy = by;
    if(bx>maxx)
      maxx = bx;
    if(by<miny)
      miny = by;
    if(bx<minx)
      minx = bx;
    
  }
  printf("Min: %i:%i Max: %i:%i\n",miny,minx,maxy,maxx);
  return 0;
}
