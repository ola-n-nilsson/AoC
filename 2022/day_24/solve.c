#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

typedef struct {
  int y;
  int x;
  char dir;
} blizzard_t;

blizzard_t blizzards[3200];
int bliz_idx = 0;

#define IN_Y (0)
#define IN_X (1)
#define EXIT_Y (36)
#define EXIT_X (100)

char fields[64][128][2048];

char possible[64][128];
char new_possible[64][128];

void printfield(int t)
{
  for(int y=0;y<37;y++)
  {
    for(int x=0;x<102;x++)
    {
      printf("%c",fields[y][x][t]);
    }
    printf("\n");
  }
}

int solve(int y, int x, int ty, int tx, int starttime)
{
  int minute = starttime;
  memset(possible,'.',sizeof(possible));
  possible[y][x] = 'E';

  while(possible[ty][tx]!='E')
  {
    memset(new_possible,'.',sizeof(new_possible));
    
    for(int y=0;y<=36;y++)  
    {
      for(int x=1;x<102;x++)
      {
        if(possible[y][x] == 'E')
        {
          // Now possible in all four directions and wait.
          if(fields[y][x][minute]=='.') //wait
          {
            new_possible[y][x] = 'E'; 
          }
          // Up
          if(y)
          {
            if(fields[y-1][x][minute]=='.')
            {
              new_possible[y-1][x] = 'E'; 
            }
          }
          // Down
          if(y<36)
          {
            if(fields[y+1][x][minute]=='.')
            {
              new_possible[y+1][x] = 'E'; 
            }
          }
          // Left
          if(fields[y][x-1][minute]=='.')
          {
            new_possible[y][x-1] = 'E'; 
          }
          // Right
          if(fields[y][x+1][minute]=='.')
          {
            new_possible[y][x+1] = 'E'; 
          }
        }
      }
    }
    memcpy(possible,new_possible,sizeof(possible));
    minute++;
  }
  return minute -1;
}

int main(int argc, char* argv[])
{
  memset(fields,'.',sizeof(fields));
  // Extract blizzards
  for(int y=0;y<(sizeof(data)/sizeof(data[0]));y++)
  {
    int len = strlen(data[y]);
    for(int x=0;x<len;x++)
    {
      char c = data[y][x];
      
      if(c == '^' || c == 'v' || c == '<' || c == '>')
      {
        blizzards[bliz_idx].y = y;
        blizzards[bliz_idx].x = x;
        blizzards[bliz_idx].dir = c;
        bliz_idx++;
      }
    }
  }
  // Build map, also in time
  for(int t=0;t<2048;t++)
  {
    for(int y=0;y<37;y++)
    {
      fields[y][0][t] = '#';
      fields[y][101][t] = '#';
    }
    for(int x=0;x<102;x++)
    {
      fields[0][x][t] = '#';
      fields[36][x][t] = '#';
    }
    fields[IN_Y][IN_X][t] = '.';
    fields[EXIT_Y][EXIT_X][t] = '.';
    // Enter blizzards
    for(int i=0;i<bliz_idx;i++)
    {
      fields[blizzards[i].y][blizzards[i].x][t] = blizzards[i].dir;
    }
    // Now move blizzards
    for(int i=0;i<bliz_idx;i++)
    {
      switch(blizzards[i].dir)
      {
        case '<':
          blizzards[i].x--;
          if(!blizzards[i].x)
          {
            blizzards[i].x = 100;
          }
          break;
        case '>':
          blizzards[i].x++;
          if(blizzards[i].x == 101)
          {
            blizzards[i].x = 1;
          }
          break;
        case 'v':
          blizzards[i].y++;
          if(blizzards[i].y == 36)
          {
            blizzards[i].y = 1;
          }
          break;
        case '^':
          blizzards[i].y--;
          if(!blizzards[i].y)
          {
            blizzards[i].y = 35;
          }
          break;
        default:
          printf("Oops\n");
          exit(-1);
      }
    }
  }

  /* printf("Field at time 0\n"); */
  /* printfield(0); */
  /* printf("Field at time 1\n"); */
  /* printfield(1); */

  int first =  solve(IN_Y, IN_X, EXIT_Y, EXIT_X, 1);
  printf("First exit at: %i minutes\n",first);
  int second = solve(EXIT_Y, EXIT_X, IN_Y, IN_X, first+1);
  printf("Second exit at: %i minutes\n",second);
  int third =  solve(IN_Y, IN_X, EXIT_Y, EXIT_X, second+1);
  printf("Third exit at: %i minutes\n",third);
  
  return 0;
}
