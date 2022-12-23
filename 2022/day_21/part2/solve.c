#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define NOT_KNOWN ((unsigned long long)18446744073709551615)

typedef enum {
#include "enum.txt"
} monkey_t;

const int nbr_monkeys = (int)END_MONKEY;

typedef struct {
  monkey_t monkey;
  unsigned long long val;
} const_monkey_t;

const_monkey_t const_monkeys[] = {
#include "numbers.txt"
};

const int nbr_const_monkeys = sizeof(const_monkeys)/sizeof(const_monkeys[0]);

typedef struct {
  monkey_t monkey;
  monkey_t op1;
  char op;
  monkey_t op2;
} monkey_op_t;

monkey_op_t ops[] = {
#include "data.txt"
};

const int nbr_ops = sizeof(ops)/sizeof(ops[0]);

char* names[] = {
#include "names.txt"
};

monkey_op_t ops_v[END_MONKEY];

unsigned long long values[END_MONKEY];

int main(int argc, char* argv[])
{
  printf("Nbr of monkeys: %i\n",nbr_monkeys);
  printf("Nbr of constant monkeys: %i\n",nbr_const_monkeys);
  printf("Nbr of op monkeys: %i\n",nbr_ops);

  memset(values, -1, sizeof(values));
  memset(ops_v, 0, sizeof(ops_v));
  // Inititate values
  for(int i=0;i<nbr_const_monkeys;i++) 
  { 
    values[const_monkeys[i].monkey] = const_monkeys[i].val; 
  }
  // Inititate ops_v
  for(int i=0;i<nbr_ops;i++)
  {
    ops_v[ops[i].monkey] = ops[i];
  }

  int last_calculated = 1;
  int calculated = 0;
  while(calculated != last_calculated)
  {
    calculated = last_calculated;
    for(int i=0;i<nbr_monkeys;i++)
    {
      if(values[i] == NOT_KNOWN)
      {
        if((ops_v[i].monkey == i) &&
           (values[ops_v[i].op1] != NOT_KNOWN) &&
           (values[ops_v[i].op2] != NOT_KNOWN))
        {
          printf("We have an op with args: %i\n",i);
          switch(ops_v[i].op)
          {
            case '+':
              values[i] = values[ops_v[i].op1] + values[ops_v[i].op2];
              calculated++;
              break;
            case '-':
              values[i] = values[ops_v[i].op1] - values[ops_v[i].op2];
              calculated++;
              break;
            case '*':
              values[i] = values[ops_v[i].op1] * values[ops_v[i].op2];
              calculated++;
              break;
            case '/':
              values[i] = values[ops_v[i].op1] / values[ops_v[i].op2];
              calculated++;
              break;
            case '=':
              // Do nothing for now.
              printf("Ready to compare: %llu and %llu\n",values[ops_v[i].op1],values[ops_v[i].op2]);
              exit(0);
              break;
            default:
              printf("Oops\n");
              exit(-1);
          }
        }
      }
    }
  }
  
#if 0
  for(int i=0;i<nbr_monkeys;i++)
  {
    if(values[i] == NOT_KNOWN)
    {
      if((values[ops_v[i].op1] != NOT_KNOWN) &&
           (values[ops_v[i].op2] != NOT_KNOWN))
      {
        printf("%s: %s %c %s\n",names[i],names[ops_v[i].op1],ops_v[i].op,names[ops_v[i].op2]);
      }
      else if((values[ops_v[i].op1] == NOT_KNOWN) &&
           (values[ops_v[i].op2] != NOT_KNOWN))
      {
        printf("%s: %s %c %llu\n",names[i],names[ops_v[i].op1],ops_v[i].op,values[ops_v[i].op2]);
      }
      else if((values[ops_v[i].op1] != NOT_KNOWN) &&
           (values[ops_v[i].op2] == NOT_KNOWN))
      {
        printf("%s: %llu %c %s\n",names[i],values[ops_v[i].op1],ops_v[i].op,names[ops_v[i].op2]);
      }
      else if((values[ops_v[i].op1] == NOT_KNOWN) &&
           (values[ops_v[i].op2] == NOT_KNOWN))
      {
        printf("%s: %llu %c %llu\n",names[i],values[ops_v[i].op1],ops_v[i].op,values[ops_v[i].op2]);
      }
    }
  }
#endif
  
  // root: pqpw = 56517685690674
  // pqpw: 3 * fhld
  // fhld: 37906634593933 - rmct
  // rmct: czst / 3
  // czst: 527 + bzrh
  // ...
  // cjhd: humn - 138

  int nidx = pqpw;
  unsigned long long val = (unsigned long long)56517685690674;

  while(nidx != humn)
  {
    if((values[ops_v[nidx].op1] == NOT_KNOWN) &&
       (values[ops_v[nidx].op2] != NOT_KNOWN))
    {
      printf("%s: %s %c %llu\t\t%016llx\n",names[nidx],names[ops_v[nidx].op1],ops_v[nidx].op,values[ops_v[nidx].op2],val);

      // val = new op const
      switch(ops_v[nidx].op)
      {
        case '+':
          val -= values[ops_v[nidx].op2];
          break;
        case '-':
          val += values[ops_v[nidx].op2];
          break;
        case '*':
          val /= values[ops_v[nidx].op2];
          break;
        case '/':
          val *= values[ops_v[nidx].op2];
          break;
        default:
          printf("Oops\n");
          exit(-1);
      }
      nidx = ops_v[nidx].op1;
    }
    else if((values[ops_v[nidx].op1] != NOT_KNOWN) &&
            (values[ops_v[nidx].op2] == NOT_KNOWN))
    {
      printf("%s: %llu %c %s\t\t%016llx\n",names[nidx],values[ops_v[nidx].op1],ops_v[nidx].op,names[ops_v[nidx].op2],val);

      // val = const op new
      switch(ops_v[nidx].op)
      {
        case '+':
          val -= values[ops_v[nidx].op1];
          break;
        case '-':
          val = values[ops_v[nidx].op1] - val;
          break;
        case '*':
          val /= values[ops_v[nidx].op1];
          break;
        case '/':
          val = values[ops_v[nidx].op1] / val;
          break;
        default:
          printf("Oops\n");
          exit(-1);
      }


      nidx = ops_v[nidx].op2;
    }
    else
    {
      printf("Oops\n");
      exit(-1);
    }
  }
  
  printf("humn should be: %llu\n",val);  //140 är fel, för lågt.

  values[humn] = val;

  //Debug through recalculate

  last_calculated = 1;
  calculated = 0;
  while(calculated != last_calculated)
  {
    calculated = last_calculated;
    for(int i=0;i<nbr_monkeys;i++)
    {
      if(values[i] == NOT_KNOWN)
      {
        if((ops_v[i].monkey == i) &&
           (values[ops_v[i].op1] != NOT_KNOWN) &&
           (values[ops_v[i].op2] != NOT_KNOWN))
        {
          printf("We have an op with args: %i\n",i);
          switch(ops_v[i].op)
          {
            case '+':
              values[i] = values[ops_v[i].op1] + values[ops_v[i].op2];
              calculated++;
              break;
            case '-':
              values[i] = values[ops_v[i].op1] - values[ops_v[i].op2];
              calculated++;
              break;
            case '*':
              values[i] = values[ops_v[i].op1] * values[ops_v[i].op2];
              calculated++;
              break;
            case '/':
              values[i] = values[ops_v[i].op1] / values[ops_v[i].op2];
              calculated++;
              break;
            case '=':
              // Do nothing for now.
              printf("Ready to compare: %llu and %llu\n",values[ops_v[i].op1],values[ops_v[i].op2]);
              exit(0);
              break;
            default:
              printf("Oops\n");
              exit(-1);
          }
        }
      }
    }
  }

  
  return 0;
}
