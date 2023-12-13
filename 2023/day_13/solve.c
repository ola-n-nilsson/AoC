#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};
int fieldcnt = 1;
unsigned long sum=0;

int cmpcol(int rx,int rrx,int starty,int maxy)
{
  int y=starty;

  while((y<(starty+maxy)) && (data[y][rx]==data[y][rrx]))
  {
    y++;
  }
  return y==starty+maxy;
}

void solve(int starty,int maxy,int maxx)
{
  printf("%i starts at %i max %i:%i\n",fieldcnt,starty,maxy,maxx);
  int reflectionrow = 0;
  int reflectioncol = 0;

  // Find reflections in rows
  for(int y=starty+1;y<(starty+maxy);y++)  // (0)  1 2 3 4 5 6
  {
    int reflection = 1;
    
    //printf("Reflection in row %i?\n",y-starty);
    for(int offset=0;((y-1-offset)>=starty) && ((y-starty+offset)<maxy);offset++)
    {
      int ry = y-offset-1;
      int rry = y+offset;
        
      //      printf("Testing %i towards %i\n",ry,rry);
      if(strcmp(data[ry],data[rry]))
      {
        reflection = 0;
        break;
      }
    }
    if(reflection)
    {
      printf("Reflection row in %i at %i\n",fieldcnt,y-starty);
      reflectionrow = 1;
      sum += (y-starty)*100;
    }
  }

  // Find reflections in columns
  for(int x=1;x<(maxx);x++)  // (0)  1 2 3 4 5 6
  {
    int reflection = 1;
    
    for(int offset=0;((x-offset-1)>=0) && ((x+offset)<maxx);offset++)
    {
      int rx = x-offset-1;
      int rrx = x+offset;
        
      //      printf("Testing %i towards %i\n",ry,rry);
      if(!cmpcol(rx,rrx,starty,maxy))
      {
        reflection = 0;
        break;
      }
    }
    if(reflection)
    {
      printf("Reflection col in %i at %i\n",fieldcnt,x);
      reflectioncol = 1;
      sum += x;
    }
  }

  if((!reflectionrow && !reflectioncol) || (reflectionrow && reflectioncol))
  {
    printf("Oops at %i match %s %s\n",fieldcnt,reflectionrow?"row":"",reflectioncol?"col":"");
    exit(-1);
  }
  
  fieldcnt++;
}

int main(int argc, char* argv[])
{
  int starty=0;
  int maxy=0;
  int maxx=0;
  int i = 0;
  
  while(i<(sizeof(data)/sizeof(data[0])))
  {
    maxy=0;
    maxx=strlen(data[i]);
    while(*data[i])
    {
      i++;
      maxy++;
    }
    solve(starty,maxy,maxx);
    i++;
    starty=i;
  }
  printf("Sum: %lu\n",sum);
  return 0;
}

// 17841 not right
