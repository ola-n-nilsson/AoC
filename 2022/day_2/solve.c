#include <stdio.h>

typedef enum {A,B,C} opponent_t; //A for Rock, B for Paper, and C for Scissors
typedef enum {X,Y,Z} mine_t; //X for Rock, Y for Paper, and Z for Scissors

// points: 1 for Rock, 2 for Paper, and 3 for Scissors plus the score for the outcome of the round 0 if you lost, 3 if the round was a draw, and 6 if you won

typedef struct {opponent_t o; mine_t m;} move_t;

const move_t moves[] = {
#include "data.txt"
};

int main(int argc,char* argv[])
{
  int score = 0;
  
  for(int i=0;i<=(sizeof(moves)/sizeof(moves[0]));i++)
  {
    switch(moves[i].o)
    {
      case A: //
        switch(moves[i].m)
        {
          case X:
            printf("AX\n");
            score += 3 + 1;
            break;
          case Y:
            printf("AY\n");
            score += 6 + 2;
            break;
          case Z:
            printf("AZ\n");
            score += 0 + 3;
            break;
        }
        break;
      case B: //
        switch(moves[i].m)
        {
          case X:
            printf("BX\n");
            score += 0 + 1;
            break;
          case Y:
            printf("BY\n");
            score += 3 + 2;
            break;
          case Z:
            printf("BZ\n");
            score += 6 + 3;
            break;
        }
        break;
      case C: //
        switch(moves[i].m)
        {
          case X:
            printf("CX\n");
            score += 6 + 1;
            break;
          case Y:
            printf("CY\n");
            score += 0 + 2;
            break;
          case Z:
            printf("CZ\n");
            score += 3 + 3;
            break;
        }
        break;
    }
  }

  printf("Score: %i\n",score);
  
  return 0;
}
