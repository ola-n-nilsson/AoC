#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

char* init_field[] = {
#include "field.txt"
};

char* moves =
#include "moves.txt"
  ;

typedef enum {
  RIGHT = 0,
  DOWN,
  LEFT,
  UP
} face_t;

#define MAX_Y (200)
#define MAX_X (150)

char field[MAX_Y][MAX_X];

int main(int argc, char* argv[])
{
  // Build field
  memset(field,' ',sizeof(field));
  for(int y=0;y<(sizeof(init_field)/sizeof(init_field[0]));y++)
  {
    int len = strlen(init_field[y]);

    for(int x=0;x<len;x++)
    {
      field[y][x] = init_field[y][x];
    }
  }
  // Start pos
  unsigned int y=0;
  unsigned int x=50;
  face_t face = RIGHT;
  char* move_p = moves;
  unsigned int lastdot;
  unsigned int nextx;
  unsigned int nexty;

  printf("F1: %c\n",field[y][x]);
  printf("F1: %c\n",field[y][x+3]);
  
  /* Rows start from 1 at the top and count downward; columns start from 1 at the left and count rightward. (In the above example, row 1, column 1 refers to the empty space with no tile on it in the top-left corner.) Facing is 0 for right (>), 1 for down (v), 2 for left (<), and 3 for up (^). The final password is the sum of 1000 times the row, 4 times the column, and the facing. */

  while(*move_p)
  {
    int steps = atoi(move_p);

    while(*move_p && isdigit(*move_p))
    {
      move_p++;
    }

    printf("At: %i:%i face %i move %i steps\n",y,x,face,steps);
    switch(face)
    {
      case RIGHT:
        lastdot = x;
        nextx = x+1;
        if(nextx == MAX_X)
        {
          nextx = 0;
        }
        while(steps && field[y][nextx] != '#')
        {
          x = nextx;
          nextx = x+1;
          if(nextx == MAX_X)
          {
            nextx = 0;
          }
          if(field[y][x] == '.')
          {
            lastdot = x;
            steps--;
          }
        }
        if(field[y][x] == ' ')
        {
          // Back to .
          x = lastdot;
        }
        break;
      case DOWN:
        lastdot = y;
        nexty = y+1;
        if(nexty == MAX_Y)
        {
          nexty = 0;
        }
        while(steps && field[nexty][x] != '#')
        {
          y = nexty;
          nexty = y+1;
          if(nexty == MAX_Y)
          {
            nexty = 0;
          }
          if(field[y][x] == '.')
          {
            lastdot = y;
            steps--;
          }
        }
        if(field[y][x] == ' ')
        {
          // Back to .
          y = lastdot;
        }
        break;
      case LEFT:
        printf("Ola: moving left %i\n",steps);
        lastdot = x;
        if(x)
          nextx = x-1;
        else
        {
          nextx = MAX_X-1;
        }
        while(steps && field[y][nextx] != '#')
        {
          x = nextx;
          if(x)
            nextx = x-1;
          else
          {
            nextx = MAX_X-1;
          }
          printf("Ola: moving left %i nextx %i\n",steps,nextx);
          if(field[y][x] == '.')
          {
            lastdot = x;
            steps--;
          }
        }
        if(field[y][x] == ' ')
        {
          // Back to .
          x = lastdot;
        }
        break;
      case UP:
        printf("Ola: moving up %i\n",steps);
        lastdot = y;
        if(y)
        {
          nexty = y-1;
        }
        else
        {
          nexty = MAX_Y-1;
        }
        printf("Ola: moving up %i nexty %i\n",steps,nexty);
        while(steps && field[nexty][x] != '#')
        {
          y = nexty;
          if(y)
          {
            nexty = y-1;
          }
          else
          {
            nexty = MAX_Y-1;
          }
          if(field[y][x] == '.')
          {
            lastdot = y;
            steps--;
          }
        }
        if(field[y][x] == ' ')
        {
          // Back to .
          y = lastdot;
        }
        break;
    }
    if(*move_p)
    {
      printf("At: %i:%i face %i turn %c\n",y,x,face,*move_p);
      switch(*move_p)
      {
        case 'L':
          switch(face)
          {
            case RIGHT:
              face = UP;
              break;
            case DOWN:
              face = RIGHT;
              break;
            case LEFT:
              face = DOWN;
              break;
            case UP:
              face = LEFT;
              break;
          }
          break;
        case 'R':
          switch(face)
          {
            case RIGHT:
              face = DOWN;
              break;
            case DOWN:
              face = LEFT;
              break;
            case LEFT:
              face = UP;
              break;
            case UP:
              face = RIGHT;
              break;
          }
          break;
      }
      move_p++;
    }
    
  }
  printf("Row: %i Col: %i Face: %i\n",y+1,x+1,face);
  printf("Pass: %i\n",(1000*(y+1))+(4*(x+1))+face);
  return 0;
}
