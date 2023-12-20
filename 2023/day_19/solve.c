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

int main(int argc, char* argv[])
{
  unsigned long sum = 0;
  
  for(int i=0;i<(sizeof(tools)/sizeof(tools[0]));i++)
  {
    ruleName_t pos = in;
    int j=0;
    
    printf("Picking up %i x=%i m=%i a=%i s=%i\n",i+1,tools[i].x,tools[i].m,tools[i].a,tools[i].s);

    while(1)
    {
      int* tocmp;

      printf("At pos: %s\n",enum2str[pos].name);
      
      // Just checking my types
      if(rules[pos].entry != pos)
      {
        printf("Oops!\n");
        exit(-1);
      }

      switch(rules[pos].actions[j].par)
      {
        case 'x':
          tocmp = &(tools[i].x);
          break;
        case 'm':
          tocmp = &(tools[i].m);
          break;
        case 'a':
          tocmp = &(tools[i].a);
          break;
        case 's':
          tocmp = &(tools[i].s);
          break;
      }

      switch(rules[pos].actions[j].cmp)
      {
        case '<':
          if(*tocmp < rules[pos].actions[j].bar)
          {
            pos = rules[pos].actions[j].dest;
            j=0;
          }
          else
          {
            j++;
          }
          break;
        case '>':
          if(*tocmp > rules[pos].actions[j].bar)
          {
            pos = rules[pos].actions[j].dest;
            j=0;
          }
          else
          {
            j++;
          }
          break;
        default:
          pos = rules[pos].actions[j].dest;
          j=0;
      }
      if(pos == ACC || pos==REJ)
      {
        if(pos == ACC)
        {
          sum += tools[i].x;
          sum += tools[i].m;
          sum += tools[i].a;
          sum += tools[i].s;
        }
        break; // Next tool
      }
    }
  }

  printf("Sum: %lu\n",sum);
  
  return 0;
}
