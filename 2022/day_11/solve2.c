#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>


/* {{73, 77} */
/* {'*',5} */
/* {'/', 11, 6, 5}}, */

typedef struct {
  char t;
  int op;
} worry_op_t;

typedef struct {
  char t;
  int op;
  int a1;
  int a2;
} action_t;

typedef struct {
  unsigned long items[40];
  worry_op_t w;
  action_t a;
  int inspections;
} monkey_descr_t;

monkey_descr_t data[] = {
#include "data.txt"
};

void move_item(int fm, int fidx, int tm)
{
  int tidx = -1;
  int i;

  // Find a slot
  for(i=0;i<40;i++)
  {
    if(!data[tm].items[i])
    {
      tidx = i;
      break;
    }
  }
  // Move
  if(tidx!=-1)
  {
    data[tm].items[tidx] = data[fm].items[fidx];
    data[fm].items[fidx] = 0;
  }
  else
  {
    printf("No idx found\n");
    exit(-1);
  }
}

int main(int argc, char* argv[])
{
  for(int turn=0;turn<10000;turn++)
  {
    for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
    {
      for(int j=0;j<40;j++)
      {
        if(data[i].items[j])
        {
          // Time to do something
          data[i].inspections++;
          switch(data[i].w.t)
          {
            case '+':
              data[i].items[j] += data[i].w.op;
              break;
            case '*':
              data[i].items[j] *= data[i].w.op;
              break;
            case '2':
              data[i].items[j] = data[i].items[j]*data[i].items[j];
              break;
            default:
              printf("Ooops!\n");
              exit(-1);
          }
          // take away all multiples of monkeys divisors
          data[i].items[j] = data[i].items[j] % 9699690;

          if(!data[i].items[j])
          {
            data[i].items[j] = data[i].a.op;
          }
          
          switch(data[i].a.t)
          {
            case '/':
              if(data[i].items[j] % data[i].a.op)
              {
                // not divisible
                move_item(i, j, data[i].a.a2);
              }
              else
              {
                // divisible
                move_item(i, j, data[i].a.a1);
              }
              break;
            default:
              printf("Ooops!\n");
              exit(-1);
          }
        }
      }
    }
  }

  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    printf("Monkey %i inspected items %i times.\n",i,data[i].inspections);
  }

  return 0;
}
