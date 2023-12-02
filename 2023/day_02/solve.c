#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef enum {
  game = 0,
  turn
} entry_t;

typedef enum {
  no = 0,
  red,
  green,
  blue
} color_t;

typedef struct
{
  entry_t entry_id;
  int op[6];
} row_t;

row_t data[] = {
#include "data.txt"
};

int main(int argc, char* argv[])
{
  int gameturn = 0;
  int max_red;
  int max_green;
  int max_blue;
  unsigned int sum = 0;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    if(data[i].entry_id == game)
    {
      if(gameturn)
      {
        // 12 red cubes, 13 green cubes, and 14 blue cubes
        if((max_red<=12) &&
           (max_green<=13) &&
           (max_blue<=14))
        {
          sum += gameturn;
          printf("Game %i possible. Sum: %u\n",gameturn, sum);
        }
      }
      gameturn = data[i].op[0];
      max_red = 0;
      max_green = 0;
      max_blue = 0;
      printf("Starting game: %i\n",gameturn);
    }
    else if (data[i].entry_id == turn)
    {
      for(int j=1;j<=5;j+=2)
      {
        if(data[i].op[j] != no)
        {
          switch(data[i].op[j])
          {
            case red:
              if(data[i].op[j-1]>max_red)
              {
                max_red = data[i].op[j-1];
              }
              break;
            case green:
              if(data[i].op[j-1]>max_green)
              {
                max_green = data[i].op[j-1];
              }
              break;
            case blue:
              if(data[i].op[j-1]>max_blue)
              {
                max_blue = data[i].op[j-1];
              }
              break;
            default:
              printf("Oops! Row: %i\n",i);
              exit(-1);
          }
        }
      }
    }
  }
  return 0;
}
