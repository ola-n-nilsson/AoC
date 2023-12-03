#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};
int maxx;
int maxy;

void findnbrandstart(int* y_p,int* x_p,int* nbr_p)
{
  int y = *y_p;
  int x = *x_p;
  int nbr = 0;

  while((data[y][x-1]>='0') && (data[y][x-1]<='9'))
  {
    x--;
  }
  // At first digit
  *y_p = y;
  *x_p = x;
  //Get the nbr also...
  while((data[y][x]>='0') && (data[y][x]<='9'))
  {
    nbr *= 10;
    nbr += (data[y][x] - '0');
    x++;
  }
  *nbr_p = nbr;
}

int find(int y, int x, int* nbrs_p)
{
  int nbrs = 0;
  int xx;
  int yy;
  int nbr;
  
  if(data[y][x]=='*')
  {
    // left?
    if((x-1)>=0)
    {
      if((data[y][x-1]>='0') && (data[y][x-1]<='9'))
      {
        nbrs++;
        xx = x-1;
        yy = y;
        findnbrandstart(&yy,&xx,&nbr);
        *nbrs_p = nbr;
        nbrs_p++;

      }
    }
    // right?
    if((x+1)<maxx)
    {
      if((data[y][x+1]>='0') && (data[y][x+1]<='9'))
      {
        nbrs++;
        xx = x+1;
        yy = y;
        findnbrandstart(&yy,&xx,&nbr);
        *nbrs_p = nbr;
        nbrs_p++;
      }
    }
    // Right above?
    if(y>=0)
    {
      if((data[y-1][x]>='0') && (data[y-1][x]<='9'))
      {
        nbrs++;
        xx = x;
        yy = y-1;
        findnbrandstart(&yy,&xx,&nbr);
        *nbrs_p = nbr;
        nbrs_p++;
      }
      else
      {
        // Two numbers above?
        // left?
        if((x-1)>0)
        {
          if((data[y-1][x-1]>='0') && (data[y-1][x-1]<='9'))
          {
            nbrs++;
            xx = x-1;
            yy = y-1;
            findnbrandstart(&yy,&xx,&nbr);
            *nbrs_p = nbr;
            nbrs_p++;
          }
        }
        // right?
        if((x+1)<maxx)
        {
          if((data[y-1][x+1]>='0') && (data[y-1][x+1]<='9'))
          {
            nbrs++;
            xx = x+1;
            yy = y-1;
            findnbrandstart(&yy,&xx,&nbr);
            *nbrs_p = nbr;
            nbrs_p++;
          }
        }
      }
    }
    // Right below?
    if((y+1)<maxy)
    {
      if((data[y+1][x]>='0') && (data[y+1][x]<='9'))
      {
        nbrs++;
        xx = x;
        yy = y+1;
        findnbrandstart(&yy,&xx,&nbr);
        *nbrs_p = nbr;
        nbrs_p++;
      }
      else
      {
        // Two numbers above?
        // left?
        if((x-1)>0)
        {
          if((data[y+1][x-1]>='0') && (data[y+1][x-1]<='9'))
          {
            nbrs++;
            xx = x-1;
            yy = y+1;
            findnbrandstart(&yy,&xx,&nbr);
            *nbrs_p = nbr;
            nbrs_p++;
          }
        }
        // right?
        if((x+1)<maxx)
        {
          if((data[y+1][x+1]>='0') && (data[y+1][x+1]<='9'))
          {
            nbrs++;
            xx = x+1;
            yy = y+1;
            findnbrandstart(&yy,&xx,&nbr);
            *nbrs_p = nbr;
            nbrs_p++;
          }
        }
      }
    }
  }
  return nbrs;
}

int main(int argc, char* argv[])
{
  maxx = strlen(data[0]);
  maxy = sizeof(data)/sizeof(data[0]);
  unsigned long sum = 0;
  
  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      int nbrs[2];
      int howmany = find(y,x,nbrs);

      if(howmany==2)
      {
        unsigned long product;
        printf("Found star at %i:%i with %i nbrs\n",y,x,howmany);
        product = nbrs[0];
        product *= nbrs[1];
        sum += product;
      }
    }
  }
  printf("Sum: %lu\n",sum);
  return 0;
}


// 78272573
