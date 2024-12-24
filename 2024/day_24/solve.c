#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef enum op_t {
  OR = 0,
  AND,
  XOR
} op_t;

typedef enum wire_t {
#include "nodes.txt"
} wire_t;

int data[] = {
#include "data.txt"
};

int values[512];

void initvalues(void)
{
#include "start.txt"
}

int main(int argc, char* argv[])
{
  int changed = 1;
  memset(values,-1,sizeof(values));
  initvalues();

  while(changed)
  {
    changed = 0;
    for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=4)
    {
      if(values[data[i+3]]==-1 && values[data[i]]!=-1 && values[data[i+2]]!=-1)
      {
        switch(data[i+1])
        {
          case OR:
            values[data[i+3]] = values[data[i]] | values[data[i+2]];
            break;
          case AND:
            values[data[i+3]] = values[data[i]] & values[data[i+2]];
            break;
          case XOR:
            values[data[i+3]] = values[data[i]] ^ values[data[i+2]];
            break;
          default:
            printf("Oops!\n");
            exit(-1);
        }
        changed++;
      }
    }
  }
  {
    unsigned long val = 0;
    printf("Z: ");
    //for(int i=z12;i>=z00;i--)
    for(int i=z45;i>=z00;i--)
    {
      printf("%i",values[i]);
      val<<=1;
      val|=values[i];
    }
    printf("\nValue: %lu\n",val);
  }
  return 0;
}
