#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#if 0
unsigned long A = 729;
unsigned long B = 0;
unsigned long C = 0;

int program[] = {0,1,5,4,3,0};
#else
unsigned long A = 38610541;
unsigned long B = 0;
unsigned long C = 0;

int program[] = {2,4,1,1,7,5,1,5,4,3,5,5,0,3,3,0};
#endif

typedef enum instr_t {
  adv = 0,
  bxl,
  bst,
  jnz,
  bxc,
  out,
  bdv,
  cdv
} instr_t;

int main(int argc, char* argv[])
{
  int pc = 0;

  while(pc<(sizeof(program)/sizeof(program[0])))
  {
    unsigned long combo;
    unsigned long literal = program[pc+1];

    if(literal<=3)
    {
      combo = literal;
    }
    else if(literal==4)
    {
      combo = A;
    }
    else if(literal==5)
    {
      combo = B;
    }
    else if(literal==6)
    {
      combo = C;
    }
    else
    {
      printf("Oops!!\n");
      exit(-1);
    }
    switch(program[pc])
    {
      case adv:
        // Divide A by 2^combo and put in A
        //        A = A/(1<<combo);
        A = A>>combo;
        pc+=2;
        break;
      case bxl:
        B = B ^ literal;
        pc+=2;
        break;
      case bst:
        B = combo & 0x7;
        pc+=2;
        break;
      case jnz:
        if(A)
        {
          pc = literal;
        }
        else
        {
          pc+=2;
        }
        break;
      case bxc:
        B = B^C;
        pc+=2;
        break;
      case out:
        printf("%lu,",combo&0x7);
        pc+=2;
        break;
      case bdv:
        // Divide A by 2^combo and put in B
        //B = A/(1<<combo);
        B = A>>combo;
        pc+=2;
        break;
      case cdv:
        // Divide A by 2^combo and put in C
        //C = A/(1<<combo);
        C = A>>combo;
        pc+=2;
        break;
      default:
        printf("Oops!\n");
        exit(-1);
        break;
    }
  }
  printf("\n");
  return 0;
}

// Tried 754345346, it's wrong...
// oh, the commas should be left in there...
