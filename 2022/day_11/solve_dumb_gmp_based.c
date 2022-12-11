#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <gmp.h>

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
  unsigned long long items[40];
  worry_op_t w;
  action_t a;
  int inspections;
} monkey_descr_t;

monkey_descr_t data[] = {
#include "data.txt"
};

mpz_t items[8][40];

void move_item(int fm, int fidx, int tm, int turn)
{
  int tidx = -1;
  int i;

  // Find a slot
  for(i=0;i<40;i++)
  {
    if(!mpz_cmp_ui(items[tm][i],0))
    {
      tidx = i;
      break;
    }
  }
  // Move
  if(tidx!=-1)
  {
    mpz_swap(items[tm][tidx], items[fm][fidx]);
    //    mpz_set_ui(items[fm][fidx],0);
  }
  else
  {
    printf("No idx found (%i)\n",turn);
    exit(-1);
  }
}

int main(int argc, char* argv[])
{
  //initialize new items
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    for(int j=0;j<40;j++)
    {
      mpz_init(items[i][j]);
      mpz_set_ui(items[i][j],data[i].items[j]);
    }
  }
  
  for(int turn=0;turn<10000;turn++)
  {
    printf("Turn: %i\n",turn);
    for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
    {
      for(int j=0;j<40;j++)
      {
        if(mpz_cmp_ui(items[i][j],0))
        {
          // Time to do something
          data[i].inspections++;
          switch(data[i].w.t)
          {
            case '+':
              mpz_add_ui(items[i][j],items[i][j],data[i].w.op);
              break;
            case '*':
              mpz_mul_ui(items[i][j],items[i][j],data[i].w.op);
              break;
            case '2':
              mpz_mul(items[i][j],items[i][j],items[i][j]);
              break;
            default:
              printf("Ooops!\n");
              exit(-1);
          }
          // Get bored
          // data[i].items[j] = data[i].items[j]/3;
          // What now?
          switch(data[i].a.t)
          {
            case '/':
              if(mpz_divisible_ui_p( items[i][j] , data[i].a.op))
              {
                // divisible
                move_item(i, j, data[i].a.a1,turn);
              }
              else
              {
                // not divisible
                move_item(i, j, data[i].a.a2,turn);
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
