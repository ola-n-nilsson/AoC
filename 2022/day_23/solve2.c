#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};
// 2446 elfs

typedef struct {
  int y;
  int x;
  int proposed_y;
  int proposed_x;
} elf_t;

elf_t elfs[3000];
int elf_idx = 0;
int miny = INT_MAX;
int maxy = INT_MIN;
int minx = INT_MAX;
int maxx = INT_MIN;

typedef struct
{
  int check1y;
  int check1x;
  int check2y;
  int check2x;
  int check3y;
  int check3x;
  int movey;
  int movex;
} move_t;

move_t moves[] = {
  {-1,-1, -1, 0, -1, 1,  -1,0},  //N
  { 1,-1,  1, 0,  1, 1,   1,0},  //S
  {-1,-1,  0,-1,  1,-1,   0,-1}, //W
  {-1, 1,  0, 1,  1, 1,   0,1}   //E
};
int move_idx = 0;

int main(int argc, char* argv[])
{
  int no_move;
  
  // Create structure.
  for(int y=0;y<(sizeof(data)/sizeof(data[0]));y++)
  {
    int len = strlen(data[y]);
    for(int x=0;x<len;x++)
    {
      if(data[y][x]=='#')
      {
        elfs[elf_idx].y = y+3000;  // Offset some
        elfs[elf_idx].x = x+3000;
        if(elfs[elf_idx].y > maxy)
          maxy = elfs[elf_idx].y;
        if(elfs[elf_idx].y < miny)
          miny = elfs[elf_idx].y;
        if(elfs[elf_idx].x > maxx)
          maxx = elfs[elf_idx].x;
        if(elfs[elf_idx].x < minx)
          minx = elfs[elf_idx].x;
        elf_idx++;
      }
    }
  }
  int rowlen = maxx-minx+6000;
  int collen = maxy-miny+6000;
  printf("Nbr of elfs: %i\n",elf_idx);
  printf("Min: %i:%i Max: %i:%i\n",miny,minx,maxy,maxx);

  int round = 1;
  while(1)
  {
    unsigned int size = sizeof(char)*(collen*rowlen);
    char* field = malloc(size);
    
    // Create a new
    memset(field,'.',size);
    for(int j=0;j<elf_idx;j++)
    {
      field[((elfs[j].y)*rowlen)+elfs[j].x] = '#';
    }
    // Count ground in smallest rectangle
    {
      int ground = 0;

      printf("Searching 1--%i:1--%i\n",(maxy-miny),(maxx-minx));
      for(int y=miny+1;y<=maxy;y++)
      {
        for(int x=minx+1;x<=maxx;x++)
        {
          //printf("%c",field[(y*rowlen) + x]);
          if(field[(y*rowlen) + x]=='.')
          {
            ground++;
          }
        }
        //printf("\n");
      }
      printf("Ground: %i\n",ground);  // 3445 to low, 3795 too low, 4034 to high, 3874
    }
    no_move = 0;
    // Find proposed moves
    for(int j=0;j<elf_idx;j++)
    {
      int y = elfs[j].y;
      int x = elfs[j].x;

      elfs[j].proposed_y = elfs[j].y;
      elfs[j].proposed_x = elfs[j].x;
      if(field[(rowlen*(y-1))+x-1] != '.' ||
         field[(rowlen*(y-1))+x] != '.' ||
         field[(rowlen*(y-1))+x+1] != '.' ||
         field[(rowlen*(y))+x-1] != '.' ||
         field[(rowlen*(y))+x+1] != '.' ||
         field[(rowlen*(y+1))+x-1] != '.' ||
         field[(rowlen*(y+1))+x] != '.' ||
         field[(rowlen*(y+1))+x+1] != '.')
      {
        for(int k=0;k<4;k++)
        {
          int midx = (move_idx + k) % 4;
          
          if(field[(rowlen*(moves[midx].check1y+y))+moves[midx].check1x+x] == '.' &&
             field[(rowlen*(moves[midx].check2y+y))+moves[midx].check2x+x] == '.' &&
             field[(rowlen*(moves[midx].check3y+y))+moves[midx].check3x+x] == '.')
          {
            // Propose a move
            elfs[j].proposed_y = elfs[j].y + moves[midx].movey;
            elfs[j].proposed_x = elfs[j].x + moves[midx].movex;
            break;
          }
        }
      }
      else
      {
        no_move++;
      }
    }
    if(no_move == elf_idx)
    {
      printf("Round: %i no moves\n",round);
      exit(0);
    }
    // Advance moves
    move_idx++;
    move_idx %= 4;

    // Clean out any elfs moving to same pos
    for(int j=0;j<elf_idx;j++)
    {
      int same = 0;
      
      for(int k=0;k<elf_idx;k++)
      {
        if(j==k)
          continue;
        if(elfs[j].proposed_y == elfs[k].proposed_y &&
           elfs[j].proposed_x == elfs[k].proposed_x)
        {
          same++;
          elfs[k].proposed_y = elfs[k].y;
          elfs[k].proposed_x = elfs[k].x;
        }
      }
      if(same)
      {
        elfs[j].proposed_y = elfs[j].y;
        elfs[j].proposed_x = elfs[j].x;
      }
    }

    // Move the elfs & calculate new min/max
    for(int j=0;j<elf_idx;j++)
    {
      elfs[j].y = elfs[j].proposed_y;
      elfs[j].x = elfs[j].proposed_x;
      if(elfs[j].y > maxy)
        maxy = elfs[j].y;
      if(elfs[j].y < miny)
        miny = elfs[j].y;
      if(elfs[j].x > maxx)
        maxx = elfs[j].x;
      if(elfs[j].x < minx)
        minx = elfs[j].x;
    }
    free(field);
    printf("Round: %i Min: %i:%i Max: %i:%i\n",round,miny,minx,maxy,maxx);
    round++;
  }

  
  return 0;
}
