#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char wind[] = {
#include "data.txt"
};
int wind_idx = 0;
int wind_len;

char field[900001][9];
int field_solid_y = 900000;  // LMF, should revers field, but don't want to make simple mistakes

/* #### */  //1  s 4 3  w 4 c 0,0 0,1 0,2 0,3

/* .#. */   //2  s 4 3  w 3 c 0,1 1,0 1,2
/* ### */
/* .#. */

/* ..# */   //3  s 4 3  w 3 c 0,0 0,1 0,2
/* ..# */
/* ### */

/* # */     //4  s 4 3  w 1 c 0,0
/* # */
/* # */
/* # */

/* ## */    //5  s 4 3 w 2 c 0,0 0,1
/* ## */

typedef struct {
  int contacts[10];
  int width;
  void (*draw_p)(int y, int x);
} shape_t;

void draw_minus(int y, int x)
{
  field[y][x] = '#';
  field[y][x+1] = '#';
  field[y][x+2] = '#';
  field[y][x+3] = '#';
}
void draw_plus(int y, int x)
{
  field[y][x+1] = '#';
  field[y-1][x] = '#';
  field[y-1][x+1] = '#';
  field[y-1][x+2] = '#';
  field[y-2][x+1] = '#';
}
void draw_L(int y, int x)
{
  field[y][x] = '#';
  field[y][x+1] = '#';
  field[y][x+2] = '#';
  field[y-1][x+2] = '#';
  field[y-2][x+2] = '#';
}
void draw_pipe(int y, int x)
{
  field[y][x] = '#';
  field[y-1][x] = '#';
  field[y-2][x] = '#';
  field[y-3][x] = '#';
}
void draw_square(int y, int x)
{
  field[y][x] = '#';
  field[y-1][x] = '#';
  field[y][x+1] = '#';
  field[y-1][x+1] = '#';
}

/* #### */  //1  s 4 3  w 4 c 0,0 0,1 0,2 0,3

/* .#. */   //2  s 4 3  w 3 c 0,1 1,0 1,2
/* ### */
/* .#. */

/* ..# */   //3  s 4 3  w 3 c 0,0 0,1 0,2
/* ..# */
/* ### */

/* # */     //4  s 4 3  w 1 c 0,0
/* # */
/* # */
/* # */

/* ## */    //5  s 4 3 w 2 c 0,0 0,1
/* ## */


// Repeat to fill unused contact. Must also contain contact to the side!!
shape_t shapes[] = {
  { {0,0,0,1,0,2,0,3,0,3}, 4, draw_minus},
  { {0,1,1,0,1,2,2,1,2,1}, 3, draw_plus},  // Can not blow in to touch 2,1 but no harm...
  { {0,0,0,1,0,2,1,2,2,2}, 3, draw_L},
  { {0,0,1,0,2,0,3,0,3,0}, 1, draw_pipe},
  { {0,0,0,1,1,0,1,1,1,1}, 2, draw_square},
};
int shape_idx = 0;


int contact(int y, int x, shape_t* s_p)
{
  int ret = 0;

  for(int i=0;i<10;i+=2)
  {
    //printf("Ola: checking contact at: %i:%i %c\n",y - s_p->contacts[i], x + s_p->contacts[i+1], field[y - s_p->contacts[i]][x + s_p->contacts[i+1]]);
    if(field[y - s_p->contacts[i]][x + s_p->contacts[i+1]] != '.')
    {
      ret = 1;
      break;
    }
  }
  
  return ret;
}

void update_solid(void)
{
  int empty = 1;
  int y = field_solid_y;

  //  printf("Ola: update_solid search from %i\n",field_solid_y);
  do {
    //printf("Ola: searching %i ",y);
    empty = 1;
    for(int x=1;x<8;x++)
    {
      //printf("%c",field[y][x]);
      if(field[y][x] != '.')
      {
        empty = 0;
        break;
      }
    }
    //printf("\n");
    y--;
  } while (!empty);
  field_solid_y = y+2;
  //printf("Ola: update_solid update to %i\n",field_solid_y);
}

void print_field(void)
{
  for(int y= 900000-50;y<900001;y++)
  {
    for(int x=0;x<9;x++)
    {
      printf("%c",field[y][x]);
    }
    printf("\n");
  }
}

int main(int argc, char* argv[])
{
  int part1 = 0;
  int last_tall = 0;
  
  // Build field
  memset(field,'.',sizeof(field));
  for(int y=0;y<=900000;y++)
  {
    field[y][0] = '|';
    field[y][8] = '|';
  }
  field[900000][0] = '+';
  field[900000][1] = '-';
  field[900000][2] = '-';
  field[900000][3] = '-';
  field[900000][4] = '-';
  field[900000][5] = '-';
  field[900000][6] = '-';
  field[900000][7] = '-';
  field[900000][8] = '+';
  wind_len = strlen(wind);
  
  for(int i=1;i<(40*wind_len);i++)
  {
    int sy,sx;
    int lasty;
    
    if(shape_idx==(sizeof(shapes)/sizeof(shapes[0])))
    {
      shape_idx = 0;
    }

    // Start_pos
    sy = field_solid_y - 4;
    sx = 3;
    lasty = 0;

    while(sy>lasty)
    {
      lasty=sy;
      //printf("Ola: pos before wind: %i:%i\n",sy,sx);
      if(wind_idx==wind_len)
      {
        //printf("Ola: wrap wind at %i\n",wind_idx);
        wind_idx = 0;
        //printf("Ola: startover at %i shape_idx %i\n",i,shape_idx);
      }

      if((wind[wind_idx]=='<') && !contact(sy,sx-1,&shapes[shape_idx]))
      {
        sx--;
      }
      if((wind[wind_idx]=='>') && !contact(sy,sx+1,&shapes[shape_idx]))
      {
        sx++;
      }
      
      wind_idx++;
      //printf("Ola: pos after wind: %i:%i\n",sy,sx);
      // Contact?
      if(contact(sy,sx,&shapes[shape_idx]) || contact(sy+1,sx,&shapes[shape_idx]))  // Should only be at +1, but just checking...
      {
        shapes[shape_idx].draw_p(sy,sx);
        update_solid();
        //        printf("{%i, %i, %i},\n",i,900000-field_solid_y,(900000-field_solid_y)- last_tall);
        last_tall = 900000-field_solid_y;
        if(i==1600)
          printf("Ola 1600: %i\n",900000-field_solid_y);
        if(i==2022)
          part1 = 900000-field_solid_y;
        if((i % 1725) == 0)
          printf("Ola height at %i %i\n",i,900000-field_solid_y);
      }
      else
      {
        sy++;
        //        printf("Ola: pos after falling: %i:%i\n",sy,sx);
      }
    }
    
    shape_idx++;
    //print_field();

  }
  //  print_field();
  printf("Solid: %i\n",field_solid_y);
  printf("Tall: %i\n",900000-field_solid_y);
  printf("Winlen: %i\n",wind_len);
  printf("Part1: %i\n",part1);
  return 0;
}
