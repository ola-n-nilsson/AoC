#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

unsigned long data[] = {
#include "data.txt"
};


int main(int argc, char* argv[])
{
  int i=0;

  while(data[i]!=(unsigned long)-1)
  {
    unsigned long b;
    unsigned long a;
    unsigned long c0,c1,c2,c3,cx,cy;
    
    //data[i+4]+=10000000000000;
    //data[i+5]+=10000000000000;

    c0=data[i+0];
    c1=data[i+1];
    c2=data[i+2];
    c3=data[i+3];
    cx=data[i+4];
    cy=data[i+5];

    
    //if(c3/c1 == c2/c0)
    {
      //printf("Parallell %i k %li %li\n",(i/6)+1,c3/c1,c2/c0);
    }
    //else
    {
      printf("var('a b')\n");
      printf("eq1 = a*%lu + b*%lu == %lu\n",c0,c2,cx);
      printf("eq2 = a*%lu + b*%lu == %lu\n",c1,c3,cy);
      printf("print(solve([eq1,eq2],a,b))\n");
    }
    i+=6;
  }
  return 0;
}
