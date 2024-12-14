#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

unsigned long data[] = {
  //#include "del1_sage_out.txt"
  //#include "out_del1_my_c.txt"
#include "out.txt"
};


int main(int argc, char* argv[])
{
  unsigned long cost = 0;

  for(int i=0;i<((sizeof(data))/(sizeof(data[0])));i+=2)
  {
    cost += data[i]*3;
    cost += data[i+1];
  }
  printf("Cost: %lu\n",cost);
  return 0;
}

// Tried 83382353039223 wrong
