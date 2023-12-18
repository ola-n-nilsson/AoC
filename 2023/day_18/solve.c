#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char field[1000][1000];
int miny = 1000;
int maxy = 0;
int minx = 1000;
int maxx = 0;

typedef struct
{
  char d;
  int len;
  char* color;
} dig_t;

dig_t data[] = {
#include "data.txt"
};


void updateminmax(int y, int x)
{
  if(y<miny)
  {
    miny = y;
  }
  if(x<minx)
  {
    minx = x;
  }
  if(y>maxy)
  {
    maxy = y;
  }
  if(x>maxx)
  {
    maxx = x;
  }
}

int fill(int y,int x)
{
  int ret = 0;

  if(field[y][x]=='F')
  {
    if(field[y-1][x]=='.')
    {
      field[y-1][x]='F';
      ret++;
      ret+=fill(y-1,x);
    }
    if(field[y+1][x]=='.')
    {
      field[y+1][x]='F';
      ret++;
      ret+=fill(y+1,x);
    }
    if(field[y][x-1]=='.')
    {
      field[y][x-1]='F';
      ret++;
      ret+=fill(y,x-1);
    }
    if(field[y][x+1]=='.')
    {
      field[y][x+1]='F';
      ret++;
      ret+=fill(y,x+1);
    }
  }
  
  return ret;
}

int main(int argc, char* argv[])
{
  int y = 200;
  int x = 200;
  int j;
  
  memset(field,'.',sizeof(field));
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    field[y][x] = '#';
    updateminmax(y,x);
    switch(data[i].d)
    {
      case 'U':
        for(j=0;j<=data[i].len;j++)
        {
          if((y-j)<0)
          {
            printf("Oops %i\n",i);
            exit(-1);
          }
          field[y-j][x] = '#';
          if(field[y-j][x+1] == '.')
          {
            field[y-j][x+1] = 'F';
          }
          updateminmax(y-j,x);
        }
        y-= data[i].len;
        break;
      case 'D':
        for(j=0;j<=data[i].len;j++)
        {
          if((y+j)>1000)
          {
            printf("Oops %i\n",i);
            exit(-1);
          }
          field[y+j][x] = '#';
          updateminmax(y+j,x);
        }
        y+= data[i].len;
        break;
      case 'L':
        for(j=0;j<=data[i].len;j++)
        {
          if((x-j)<0)
          {
            printf("Oops %i\n",i);
            exit(-1);
          }
          field[y][x-j] = '#';
          updateminmax(y,x-j);
        }
        x-= data[i].len;
        break;
      case 'R':
        for(j=0;j<=data[i].len;j++)
        {
          if((x+j)>1000)
          {
            printf("Oops %i\n",i);
            exit(-1);
          }
          field[y][x+j] = '#';
          updateminmax(y,x+j);
        }
        x+= data[i].len;
        break;
      default:
        printf("Oops\n");
        exit(-1);
    }
  }

  //Fill
  {
    int filled = 1;

    while(filled)
    {
      filled = 0;
      for(y=miny;y<=maxy;y++)
      {
        for(x=minx;x<=maxx;x++)
        {
          filled += fill(y,x);
        }
      }
    }
  }
  
  // Print
  for(y=miny;y<=maxy;y++)
  {
    for(x=minx;x<=maxx;x++)
    {
      printf("%c",field[y][x]);
    }
    printf("\n");
  }

  // Count
  {
    int cnt = 0;

    for(y=miny;y<=maxy;y++)
    {
      for(x=minx;x<=maxx;x++)
      {
        if(field[y][x] == '#' || field[y][x] == 'F')
        {
          cnt++;
        }
      }
    }
    printf("Count: %i\n",cnt);
  }
  
  return 0;
}
