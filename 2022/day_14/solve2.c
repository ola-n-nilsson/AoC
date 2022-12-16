#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

char field[1000][1000];

int minx = 1001;
int maxx = 0;
int miny = 1001;
int maxy = 0;

void print_field(void)
{
  int x,y;
  for(y=0;y<=maxy;y++)
  {
    for(x=(minx-200);x<=(maxx+200);x++)
    {
      printf("%c",field[y][x]);
    }
    printf("\n");
  }
}

void drop_sand(int* y, int* x)
{
  int sx = 500;
  int sy = 0;
  int lastx = 0;
  int lasty = 1;
  
  while(sx != lastx || sy != lasty)
  {
    lastx = sx;
    lasty = sy;
    
    if(sx<10 || sx>990 || sy>170) // Should always end on the Y...
    {
      // Fell of the field!
      return;
    }
    if(field[sy+1][sx]=='.')
    {
      field[sy][sx]='.';
      field[sy+1][sx]='0';
      sy++;
    }
    else if(field[sy+1][sx-1]=='.')
    {
      field[sy][sx]='.';
      field[sy+1][sx-1]='0';
      sy++;
      sx--;
    }
    else if(field[sy+1][sx+1]=='.')
    {
      field[sy][sx]='.';
      field[sy+1][sx+1]='0';
      sy++;
      sx++;
    }
  }
  *y = sy;
  *x = sx;
}

int main(int argc, char* argv[])
{
  memset(field,'.',sizeof(field));
         
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    char *p = data[i];
    int sx;
    int sy;
    int ex;
    int ey;
    
    // 487,113 -> 492,113
    sscanf(p,"%i,%i",&ex,&ey);

    while(*p)
    {
      sx = ex;
      sy = ey;

      while(*p && *p!='-')
        p++;
      if(*p)
        p++;
      if(*p && *p!='>')
      {
        printf("Oops\n");
        exit(-1);
      }
      if(*p)
        p++;
      if(*p && *p!=' ')
      {
        printf("Oops\n");
        exit(-1);
      }
      if(*p)
        p++;
      sscanf(p,"%i,%i",&ex,&ey);
      if(sx<minx)
        minx = sx;
      if(sx>maxx)
        maxx = sx;
      if(sy<miny)
        miny = sy;
      if(sy>maxy)
        maxy = sy;
      if(ex<minx)
        minx = ex;
      if(ex>maxx)
        maxx = ex;
      if(ey<miny)
        miny = ey;
      if(ey>maxy)
        maxy = ey;
      
      printf("%i: from %i:%i to %i:%i\n",i,sy,sx,ey,ex);
      if(sx!=ex && sy!=ey)
      {
        printf("Oops\n");
        exit(-1);
      }
      else if(sx!=ex)
      {
        if(sx>ex)
        {
          for(int ix=ex;ix<=sx;ix++)
            field[sy][ix] = '#';
        }
        else
        {
          for(int ix=sx;ix<=ex;ix++)
            field[sy][ix] = '#';
        }
      }
      else if(sy!=ey)
      {
        if(sy>ey)
        {
          for(int iy=ey;iy<=sy;iy++)
            field[iy][sx] = '#';
        }
        else
        {
          for(int iy=sy;iy<=ey;iy++)
            field[iy][sx] = '#';
        }
      }
      
    }
    
  }
  {
    for(int x=10;x<=990;x++)
    {
      field[164][x] = '#';
    }
    maxy+=2;
  }
  {
    int y = 0;
    int x = 0;
    int i = 0;
    
    while(y != -1 && x!=-1)
    {
      y = -1;
      x = -1;
      drop_sand(&y,&x);
      if(x>0 && y>0)
      {
        i++;
      }
      printf("Ended at: %i:%i\n",y,x);
      if(x==500&&y==0)
      {
        break;
      }
    }

    print_field();
    printf("Sand that stayed: %i\n",i);

  }

  printf("Min: %i:%i Max: %i:%i\n",miny,minx,maxy,maxx);

  return 0;
}
