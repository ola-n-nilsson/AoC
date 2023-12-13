#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};
int fieldcnt = 1;
unsigned long sum=0;
char field[100][100];

typedef struct
{
  int isrow;
  int num;
} part1_sol_t;

part1_sol_t part1[150];

int cmpcol(int rx,int rrx,int starty,int maxy)
{
  int y=starty;

  while((y<(starty+maxy)) && (field[y][rx]==field[y][rrx]))
  {
    y++;
  }
  return y==starty+maxy;
}

int solve(int starty,int maxy,int maxx, int ispart1)
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
      if(strcmp(field[ry],field[rry]))
      {
        reflection = 0;
        break;
      }
    }
    if(reflection)
    {
      if(!ispart1)
      {
        if(!part1[fieldcnt-1].isrow || (part1[fieldcnt-1].num!=(y-starty)))
        {
          printf("Reflection row in %i at %i\n",fieldcnt,y-starty);
          reflectionrow = 1;
          sum += (y-starty)*100;
        }
      }
      else
      {
        printf("Part1 reflection row in %i at %i\n",fieldcnt,y-starty);
        reflectionrow = 1;
        part1[fieldcnt-1].isrow = 1;
        part1[fieldcnt-1].num = y-starty;
      }
    }
  }

  if(!reflectionrow)
  {
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
        if(!ispart1)
        {
          if(part1[fieldcnt-1].isrow || (part1[fieldcnt-1].num!=x))
          {
            printf("Reflection col in %i at %i\n",fieldcnt,x);
            reflectioncol = 1;
            sum += x;
          }
        }
        else
        {
          printf("Part1 reflection col in %i at %i\n",fieldcnt,x);
          reflectioncol = 1;
          part1[fieldcnt-1].isrow = 0;
          part1[fieldcnt-1].num = x;
        }
      }
    }
  }
  
  return reflectionrow + reflectioncol;
}

int main(int argc, char* argv[])
{
  int maxy=0;
  int maxx=0;
  int i = 0;
  
  while(i<(sizeof(data)/sizeof(data[0])))
  {
    memset(field,0,sizeof(field));
    maxy=0;
    maxx=strlen(data[i]);
    while(*data[i])
    {
      strcpy(field[maxy],data[i]);
      i++;
      maxy++;
    }
    {
      int found = 0;

      solve(0,maxy,maxx,1); 

      for(int y=0;(y<maxy)&&!found;y++)
      {
        for(int x=0;(x<maxx)&&!found;x++)
        {
          if(field[y][x]=='.')
          {
            field[y][x]='#';
          }
          else
          {
            field[y][x]='.';
          }
          found = solve(0,maxy,maxx,0);
          if(field[y][x]=='.')
          {
            field[y][x]='#';
          }
          else
          {
            field[y][x]='.';
          }
        }
      }
    }
    i++;
    fieldcnt++;
  }
  printf("Sum: %lu\n",sum);
  return 0;
}

