#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#if 0
unsigned long A = 2024;
unsigned long B = 0;
unsigned long C = 0;

int program[] = {0,3,5,4,3,0};
#else
unsigned long A = 38610541;
unsigned long B = 0;
unsigned long C = 0;

int program[] = {2,4,1,1,7,5,1,5,4,3,5,5,0,3,3,0};
#endif

int generates[8][0x400];
int gidx[8];

#if 0
  2,4, B = A & 0x7   ->> Max 0x6
  1,1, B = 1 ^ B     ->> Blir 0x7
  7,5, C = A>>B  -> max 7 bitar över nuvarande A som påverkar
  1,5, B = 5 ^ B
  4,3, B = B ^ C
  5,5, Out(B & 0x7)
  0,3, A = A/8                       ->> Talet måste vara 3*16 bitar långt
  3,0  JMP 0 så länge A inte är 0
#endif

int firstgenerated[0x400];    
    
// First
//  111 111 111 111 111 111 111 111 111 111 111 111 111 111 111 111
//                                                              BBB
//                                                    C CCC CCC CCC 0x400
// mask                                               1 111 111 111 0x3FF

// Second
//  111 111 111 111 111 111 111 111 111 111 111 111 111 111 111 111
//                                                              BBB
//                                                    C CCC CCC CCC
//                                                          BBB
//                                                C CCC CCC CCC
//                                                               ^ Several matching BBB
//                                                           ^ But now we must select one that fits here

// 0 000 000 111 111 111 111 111 111 111 111 111 111 111 111 111 111 111 111
// 0 000 000 CCC  <- för sista outputen
//     0 000 ^^^ CCC <- för näst sista outputten

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


void search(int pc,unsigned long nbr)
{
  int idx = (nbr<<3)&0x3FF;
  
  if(pc==-1)
  {
    // Winner!!
    printf("Nbr: %lu\n",nbr);
    return;
  }
  for(int i=0;i<8;i++)
  {
    if(firstgenerated[idx+i]==program[pc])
    {
      search(pc-1,(nbr<<3)|i);
    }
  }
}


int main(int argc, char* argv[])
{
  memset(generates,0,sizeof(generates));
  memset(gidx,0,sizeof(gidx));

  for(int SA = 0;SA<0x400;SA++)
  {
    int pc = 0;
    int idx = 0;
    
    A = SA;
    B = 0;
    C = 0;

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
          if(!idx)
          {
            firstgenerated[SA] = combo&0x7;
            generates[combo&0x7][gidx[combo&0x7]++] = SA-1;
          }
          idx++;
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
  }

  search((sizeof(program)/sizeof(program[0]))-1,0);
  return 0;
}

