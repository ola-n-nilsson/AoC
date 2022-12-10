#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef enum {
  addx,
  noop
} op_t;

typedef struct {
  op_t op;
  int val;
} inst_t;
  
const inst_t data[] = {
#include "data.txt"
};

int main(int argc, char* argv[])
{
  int op_idx = 0;
  int op_del = 0;
  int x = 1;
  
  for(int c=1;c<221;c++)
  {
    if(op_del)
    {
      op_del--;
      if(op_del)
      {
        printf("C: %i delay x %i\n",c,x);
      }
      else
      {
        printf("C: %i addx x %i\n",c,x);
        x += data[op_idx].val;
        op_idx++;
      }
    }
    else
    {
      switch(data[op_idx].op)
      {
        case addx:
          printf("C: %i start_addx x %i\n",c,x);
          op_del = 1;
          break;
        case noop:
          printf("C: %i noop x %i\n",c,x);
          op_idx++;
          break;
        default:
          printf("Oops\n");
          exit(-1);
      }
    }
  }
  return 0;
}
