#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>


const int data[] = {
#include "data.txt"
};

int inside(int y,int x)
{
  int cross = 0;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=2)
  {
    int j = (i+2)%(sizeof(data)/sizeof(data[0]));

    if(data[i+1]-data[j+1]) //There is a diff in y for this segment
    {
      int miny = data[i+1] < data[j+1] ? data[i+1] : data[j+1];
      int maxy = data[i+1] > data[j+1] ? data[i+1] : data[j+1];

      if((data[i]==x) && (y>=miny) && (y<=maxy))
      {
        return 1;
      }
      if((x>data[i]) && (y>miny) && (y<=maxy))
      {
        cross++;
      }
    }
    else
    {
      int minx = data[i] < data[j] ? data[i] : data[j];
      int maxx = data[i] > data[j] ? data[i] : data[j];

      if((data[i+1]==y) && (x>=minx) && (x<=maxx))
      {
        return 1;
      }
    }
  }
  return cross&1;
}

int uncrossed(int y,int x,int ydiff, int xdiff)
{
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=2)
  {
    int j = (i+2)%(sizeof(data)/sizeof(data[0]));

    //If this point is within rectangle we're done
    if((data[i]>x) && (data[i]<(x+xdiff)) &&
       (data[i+1]>y) && (data[i+1]<(y+ydiff)))
    {
      return 0;
    }
    
    if(data[i+1]-data[j+1]) //There is a diff in y for this segment
    {
      int miny = data[i+1] < data[j+1] ? data[i+1] : data[j+1];
      int maxy = data[i+1] > data[j+1] ? data[i+1] : data[j+1];

      if((data[i]>x) && (data[i]<(x+xdiff)))
      {
        // If crosses our y we're done.
        if((y>=miny && y<maxy) ||
           ((y+ydiff)>miny && (y+ydiff)<=maxy))
        {
          return 0;
        }
      }
    }
    else
    {
      int minx = data[i] < data[j] ? data[i] : data[j];
      int maxx = data[i] > data[j] ? data[i] : data[j];

      if((data[i+1]>y) && (data[i+1]<(y+ydiff)))
      {
        // If crosses our x we're done.
        if((x>=minx && x<maxx) ||
           ((x+xdiff)>minx && (x+xdiff)<=maxx))
        {
          return 0;
        }
      }
    }
  }

  return 1;
}

int main(int argc, char* argv[])
{
  unsigned long marea = 0;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=2)
  {
    for(int j=0;j<(sizeof(data)/sizeof(data[0]));j+=2)
    {
      if(i!=j)
      {
        int xdiff = data[i] > data[j] ? (data[i]-data[j]) : (data[j]-data[i]);
        int ydiff = data[i+1] > data[j+1] ? (data[i+1]-data[j+1]) : (data[j+1]-data[i+1]);
        int x = data[i] < data[j] ? data[i] : data[j];
        int y = data[i+1] < data[j+1] ? data[i+1] : data[j+1];

        if(xdiff && ydiff && inside(y+1,x+1))
        {
          unsigned long area = (unsigned long)(xdiff+1)*(ydiff+1);
          
          if((area>marea) &&
             uncrossed(y,x,ydiff,xdiff))
          {
            printf("New marea %lu for %i %i\n",area,i/2,j/2);
            marea = area;
          }
        }
      }    
    }
  }
  
  printf("Max area: %lu\n",marea);

  return 0;
}


