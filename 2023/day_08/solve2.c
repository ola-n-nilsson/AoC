#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "data2.h"

int main(int argc, char* argv[])
{
  unsigned long product = 1;
  
  for(int s=0;s<(sizeof(startnodes)/sizeof(startnodes[0]));s++)
  {
    node_t now = startnodes[s];
    unsigned int steps = 0;
    char* instruction = instructions;
    unsigned int visited[ZZZ+6];

    memset(visited,0,sizeof(visited));

    printf("Instruction len: %i\n",(int)strlen(instructions));
    
    while(!visited[now])
    {
      visited[now] = steps;
      steps++;
      switch(*instruction)
      {
        case 'L':
          now = nodes[now][1];
          break;
        case 'R':
          now = nodes[now][2];
          break;
        default:
          printf("Ooops!\n");
          exit(-1);
      }
    
      instruction++;
      if(!(*instruction))
      {
        instruction = instructions;
      }
    }

    printf("Returned after %u steps first visit %u for startnode: %i\n",steps - visited[now], visited[now],s);
    product *= (steps - visited[now]);
  }
  printf("Product: %lu\n",product*strlen(instructions));
  return 0;
}

// Not fully sure I did this correcly, but muliplying all the primes gave the right answer. 
