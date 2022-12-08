#include <stdio.h>

typedef enum {A,B,C} opponent_t; //A for Rock, B for Paper, and C for Scissors
typedef enum {X,Y,Z} mine_t; //X means you need to lose, Y means you need to end the round in a draw, and Z means you need to win.

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
            printf("AX\n"); // Rock + loose = Rock + sc
            score += 0 + 3;
            break;
          case Y:
            printf("AY\n"); // Rock + draw = rock + rock
            score += 3 + 1;
            break;
          case Z:
            printf("AZ\n");  // Rock + win = rock + paper
            score += 6 + 2;
            break;
        }
        break;
      case B: //
        switch(moves[i].m)
        {
          case X:
            printf("BX\n");  // Paper + loose = paper + rock
            score += 0 + 1;
            break;
          case Y:
            printf("BY\n");  // Paper + draw = paper + paper
            score += 3 + 2;
            break;
          case Z:
            printf("BZ\n");  // Paper + win = paper + sc
            score += 6 + 3;
            break;
        }
        break;
      case C: //
        switch(moves[i].m)
        {
          case X:
            printf("CX\n");  //Sc + loose = Sc + paper
            score += 0 + 2;
            break;
          case Y:
            printf("CY\n"); // Sc + draw = Sc + Sc
            score += 3 + 3;
            break;
          case Z:
            printf("CZ\n");  // Sc + win = Sc + rock
            score += 6 + 1;
            break;
        }
        break;
    }
  }

  printf("Score: %i\n",score);
  
  return 0;
}
