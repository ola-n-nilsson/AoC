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

typedef struct {
  unsigned int y1;
  unsigned int y2;
  unsigned int x1;
  unsigned int x2;
  face_t face;
  unsigned int toy1;
  unsigned int toy2;
  unsigned int tox1;
  unsigned int tox2;
  face_t new_face;
} fold_t;

fold_t foldes[] = {
  { 0,0,50,99,UP,150,199,0,0,RIGHT}, //1
  { 150,199,0,0,LEFT,0,0,50,99,DOWN},  //1
  { 150,199,49,49,RIGHT,149,149,50,99,UP }, //2
  { 149,149,50,99,DOWN,150,199,49,49,LEFT}, //2
  { 50,99,50,50,LEFT,100,100,0,49,DOWN},  //3
  { 100,100,0,49,UP,50,99,50,50,RIGHT}, //3
  { 0,49,50,50,LEFT,149,100,0,0,RIGHT},  //4
  { 100,149,0,0,LEFT,49,0,50,50,RIGHT},  //4
  { 0,49,149,149,RIGHT,149,100,99,99,LEFT}, //5
  { 100,149,99,99,RIGHT,49,0,149,149,LEFT}, //5
  { 49,49,100,149,DOWN,50,99,99,99,LEFT}, //6
  { 50,99,99,99,RIGHT,49,49,100,149,UP}, //6
  { 0,0,100,149,UP,199,199,0,49,UP}, //7
  { 199,199,0,49,DOWN,0,0,100,149,DOWN}  //7
};

void findnext(unsigned int y,unsigned int x,face_t face,unsigned int* nexty,unsigned int* nextx,face_t* nextface)
{
  //First find folds
  for(int i=0;i<(sizeof(foldes)/sizeof(foldes[0]));i++)
  {
    if( (y >= foldes[i].y1) && (y <= foldes[i].y2) &&
        (x >= foldes[i].x1) && (x <= foldes[i].x2) &&
        (foldes[i].face == face))
    {
      //We are at this fold
      printf("Ola: before fold %u:%u %i\n",y,x,face);
      printf("Ola: at fold %i (idx: %i)\n",(i/2)+1,i);
      if(foldes[i].x1 == foldes[i].x2)
      {
        // Going from a column
        if(foldes[i].tox1 == foldes[i].tox2)
        {
          // Going to a column
          int deltay = (int)y - foldes[i].y1;  // How far into range?
          *nextx = foldes[i].tox1;
          if(foldes[i].toy1 > foldes[i].toy2)
          {
            *nexty = foldes[i].toy1 - deltay;
          }
          else
          {
            *nexty = foldes[i].toy1 + deltay;
          }
        }
        else
        {
          // Going to a row
          int delta = (int)y - foldes[i].y1;  // How far into range?
          *nexty = foldes[i].toy1;
          if(foldes[i].tox1 > foldes[i].tox2)
          {
            *nextx = foldes[i].tox1 - delta;
          }
          else
          {
            *nextx = foldes[i].tox1 + delta;
          }
        }
      }
      else
      {
        // Going from a row
        if(foldes[i].tox1 == foldes[i].tox2)
        {
          // Going to a column
          int delta = (int)x - foldes[i].x1;  // How far into range?
          *nextx = foldes[i].tox1;
          if(foldes[i].toy1 > foldes[i].toy2)
          {
            *nexty = foldes[i].toy1 - delta;
          }
          else
          {
            *nexty = foldes[i].toy1 + delta;
          }
        }
        else
        {
          // Going to a row
          int deltax = (int)x - foldes[i].x1;  // How far into range?
          *nexty = foldes[i].toy1;
          if(foldes[i].tox1 > foldes[i].tox2)
          {
            *nextx = foldes[i].tox1 - deltax;
          }
          else
          {
            *nextx = foldes[i].tox1 + deltax;
          }
        }
      }
      *nextface = foldes[i].new_face;
      printf("Ola: after fold %u:%u %i\n",*nexty,*nextx,*nextface);
      return;
    }
  }
  // We are not at a fold
  *nextface = face;
  *nextx = x;
  *nexty = y;
  switch(face)
  {
    case UP:
      (*nexty)--;
      break;
    case DOWN:
      (*nexty)++;
      break;
    case LEFT:
      (*nextx)--;
      break;
    case RIGHT:
      (*nextx)++;
      break;
  }
}


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
#if 0
  unsigned int lastdotx;
  unsigned int lastdoty;
  face_t lastface;
#endif
  unsigned int nextx;
  unsigned int nexty;
  face_t nextface;
  
  /* Rows start from 1 at the top and count downward; columns start from 1 at the left and count rightward. (In the above example, row 1, column 1 refers to the empty space with no tile on it in the top-left corner.) Facing is 0 for right (>), 1 for down (v), 2 for left (<), and 3 for up (^). The final password is the sum of 1000 times the row, 4 times the column, and the facing. */

  while(*move_p)
  {
    int steps = atoi(move_p);

    while(*move_p && isdigit(*move_p))
    {
      move_p++;
    }

    printf("At: %i:%i face %i move %i steps\n",y,x,face,steps);

    do
    {
      findnext(y,x,face,&nexty,&nextx,&nextface);
      if(field[nexty][nextx] != '#')
      {
        y = nexty;
        x = nextx;
        face = nextface;
      }
      steps--;
    } while(steps && field[nexty][nextx] != '#');


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
  printf("Pass: %i\n",(1000*(y+1))+(4*(x+1))+face); // 38240 wrong. To high. 116141, 90210
  return 0;
}
