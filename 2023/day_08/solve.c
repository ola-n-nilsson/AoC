#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "data.h"

int main(int argc, char* argv[])
{
  node_t now = AAA;
  int steps = 0;
  char* instruction = instructions;
  while(now != ZZZ)
  {
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

  printf("Reached ZZZ in %i steps\n",steps);
  
  return 0;
}
