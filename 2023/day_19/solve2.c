#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#if 1
typedef enum 
{
#include "datar.txt"
} ruleName_t;

typedef struct
{
  ruleName_t pos;
  char* name;
} enumstr_t;

enumstr_t enum2str[] = 
{
#include"datastr.txt"
};

typedef struct
{
  ruleName_t dest;
  char par;
  char cmp;
  int bar;
} action_t;

typedef struct
{
  ruleName_t entry;
  action_t actions[5];
} rule_t;

rule_t rules[] = {
#include "data.txt"
};

typedef struct
{
  int x;
  int m;
  int a;
  int s;
} tool_t;

tool_t tools[] = {
#include "datab.txt"
};

#else
typedef enum 
{
#include "datar2.txt"
} ruleName_t;

typedef struct
{
  ruleName_t pos;
  char* name;
} enumstr_t;

enumstr_t enum2str[] = 
{
#include"datastr2.txt"
};

typedef struct
{
  ruleName_t dest;
  char par;
  char cmp;
  int bar;
} action_t;

typedef struct
{
  ruleName_t entry;
  action_t actions[5];
} rule_t;

rule_t rules[] = {
#include "data2.txt"
};

typedef struct
{
  int x;
  int m;
  int a;
  int s;
} tool_t;

tool_t tools[] = {
#include "datab2.txt"
};

#endif

unsigned long cnt = 0;

void traverse(ruleName_t pos, int* limits)
{
  int j=0;

  if(pos == ACC)
  {
    printf("Acc limits: ");
    for(int k=0;k<8;k++)
    {
      printf("%i ",limits[k]);
    }
    printf("\n");
    cnt += ((unsigned long)(limits[1]-limits[0]+1))*(limits[3]-limits[2]+1)*(limits[5]-limits[4]+1)*(limits[7]-limits[6]+1);
    printf("Cnt: %lu\n",cnt);
    return;
  }
  else if(pos == REJ || pos == NAN)
  {
    return;
  }

  while(rules[pos].actions[j].dest != NAN)
  {
    printf("Traverse %s %i\n",enum2str[pos].name,j);

    switch(rules[pos].actions[j].cmp)
    {
      case '<':
        {
          int loclimits[8];
          int* mod = NULL;
          int* mod2 = NULL;
          memcpy(loclimits,limits,sizeof(loclimits));
        
          switch(rules[pos].actions[j].par)
          {
            case 'x':
              mod=&(loclimits[0]);
              mod2=&(limits[0]);
              break;
            case 'm':
              mod=&(loclimits[2]);
              mod2=&(limits[2]);
              break;
            case 'a':
              mod=&(loclimits[4]);
              mod2=&(limits[4]);
              break;
            case 's':
              mod=&(loclimits[6]);
              mod2=&(limits[6]);
              break;
          }
        
          if(mod[1]>rules[pos].actions[j].bar)
          {
            mod[1] = rules[pos].actions[j].bar-1;
          }
          traverse(rules[pos].actions[j].dest,loclimits);

          if(mod2[0]<rules[pos].actions[j].bar)
          {
            mod2[0] = rules[pos].actions[j].bar;
          }
        }        
        break;
      case '>':
        {
          int loclimits[8];
          int* mod = NULL;
          int* mod2 = NULL;
        
          memcpy(loclimits,limits,sizeof(loclimits));

          switch(rules[pos].actions[j].par)
          {
            case 'x':
              mod=&(loclimits[0]);
              mod2=&(limits[0]);
              break;
            case 'm':
              mod=&(loclimits[2]);
              mod2=&(limits[2]);
              break;
            case 'a':
              mod=&(loclimits[4]);
              mod2=&(limits[4]);
              break;
            case 's':
              mod=&(loclimits[6]);
              mod2=&(limits[6]);
              break;
          }
        
          if(mod[0]<rules[pos].actions[j].bar)
          {
            mod[0] = rules[pos].actions[j].bar+1;
          }
          traverse(rules[pos].actions[j].dest,loclimits);

          if(mod2[1]>rules[pos].actions[j].bar)
          {
            mod2[1] = rules[pos].actions[j].bar;
          }

        }
        break;
      default:
        traverse(rules[pos].actions[j].dest,limits);
        break;
    }
    j++;
  }
}

int main(int argc, char* argv[])
{
  int limits[] = {1,4000,1,4000,1,4000,1,4000};
  
  traverse(in,limits);
  
  printf("Cnt: %lu\n",cnt);
  
  return 0;
}


