#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data_in[] = {
#include "data.txt"
};

char data[40][60];
char dirmap[40][160];
int vismap[40][160];

int sy = -1;
int sx = -1;
int ey = -1;
int ex = -1;
int my = -1;
int mx = -1;
int min_cnt = -1;

const char hex[] = "0123456789abcdef";


int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int trymove(int y,int x,int cnt)
{
  char* order = "rudl";
  int b[4] = {-1,-1,-1,-1};
    
  if(vismap[y][x]==-1)
  {
    //no circles
    return -1;
  }
  vismap[y][x] = -1; //Assume no path from here.

  printf("Visit: %i:%i (%c)\n",y,x,hex[(int)dirmap[y][x]]);

  if(ex==x && ey==y)
  {
    printf("Path with %i steps at %i:%i\n",cnt,y,x);
    /* if((min_cnt == -1) || (cnt<min_cnt)) */
    /* { */
    /*   min_cnt = cnt; */
    /*   printf("Path with %i steps\n",cnt); */
    /* } */
    /* else */
    /* { */
    /*   printf("."); */
    /* } */
    vismap[y][x] = -2; //Goal!
    return 0;
  }
  // Adaptive search order
  if(x>ex)
  {
    order = "ldur";
  }
  else if(x==ex)
  {
    if(y>ey)
    {
      order = "urld";
    }
    else
    {
      order = "dlru";
    }
  }
  printf("Search %i:%i in order %s\n",y,x,order);
  for(int i=0;i<4;i++)
  {
    switch(order[i])
    {
      // int idx = pl + (pr<<1) + (pu<<2) + (pd<<3);
      case 'u':
        if(y && (dirmap[y][x]&(1<<2)))
        {
          printf("Search u from %i:%i\n",y,x);
          b[0] = trymove(y-1,x,cnt+1);
        }
        break;
      case 'd':
        if((y+1<my) && (dirmap[y][x]&(1<<3)))
        {
          printf("Search d from %i:%i\n",y,x);
          b[1] = trymove(y+1,x,cnt+1);
        }
        break;
      case 'l':
        if(x && (dirmap[y][x]&1))
        {
          printf("Search l from %i:%i\n",y,x);
          b[2] = trymove(y,x-1,cnt+1);
        }
        break;
      case 'r':
        if(((x+1)<mx) && (dirmap[y][x]&(1<<1)))
        {
          printf("Search r from %i:%i\n",y,x);
          b[3] = trymove(y,x+1,cnt+1);
        }
        break;
      default:
        printf("Oops\n");
        exit(-1);
    }
  }

  qsort (b, 4, sizeof(int), comp);
  for(int i=0;i<4;i++)
  {
    if(b[i]>-1)
    {
      //Shortest path
      vismap[y][x] = b[i]+1;
      return b[i]+1;
    }
  }
    
  return -1; 
}


int main(int argc, char* argv[])
{
  my = sizeof(data_in)/sizeof(data_in[0]);
  mx = strlen(data_in[0]);

  int pu,pd,pl,pr;
  
  memset(dirmap,' ',sizeof(dirmap));
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
  data[ey][ex]='z';  // E has elevation z
  
  for(int y=0;y<my;y++)
  {
    for(int x=0;x<mx;x++)
    {
      pu = 0;
      pd = 0;
      pl = 0;
      pr = 0;

      // Left?
      if(x && ((data[y][x-1] - data[y][x]) <= 1) && (data[y][x-1] != 'S'))
      {
        pl = 1;
      }
      // Right?
      if(((x+1)<mx) && ((data[y][x+1] - data[y][x]) <= 1)  && (data[y][x+1] != 'S'))
      {
        pr = 1;
      }
      // Up?
      if(y && ((data[y-1][x] - data[y][x]) <= 1)  && (data[y-1][x] != 'S'))
      {
        pu = 1;
      }
      // Down?
      if(((y+1)<my) && ((data[y+1][x] - data[y][x]) <= 1)  && (data[y+1][x] != 'S'))
      {
        pd = 1;
      }
      {
        int idx = pl + (pr<<1) + (pu<<2) + (pd<<3);
        dirmap[y][x] = idx;
      }
    }
  }

  /* dirmap[ey][ex] = 'E'; */
  /* for(int y=0;y<my;y++) */
  /* { */
  /*   for(int x=0;x<mx;x++) */
  /*   { */
  /*     printf("%c",dirmap[y][x]); */
  /*   } */
  /*   printf("\n"); */
  /* } */
  /* printf("\n"); */

  dirmap[ey][ex] = 0xf; //No limit at the E
  dirmap[sy][sx] = 0xf; //No move at S

  trymove(sy,sx,0);

  printf("S: %i:%i E: %i:%i\n",sy,sx,ey,ex);
  printf("max: %i:%i\n",my,mx);
  return 0;
}
