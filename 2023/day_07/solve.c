#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef enum {
  NO = 0,
  HIGH,
  PAIR,
  TPAIR,
  KIND3,
  FULL,
  KIND4,
  KIND5
} class_t;

typedef struct
{
  char* hand;
  int bid;
  class_t class;
} hand_t;

hand_t data[] = {
#include "data.txt"
};

int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f < s) return  1;
    if (f > s) return -1;
    return 0;
}

void classify()
{
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    int cnts[5] = {0,0,0,0,0};
    
    for(int j=0;j<5;j++)
    {
      for(int k=0;k<5;k++)
      {
        if(j!=k)
        {
          if(data[i].hand[j] == data[i].hand[k])
          {
            cnts[j]++;
          }
        }
      }
    }
    qsort (cnts, sizeof(cnts)/sizeof(cnts[0]), sizeof(cnts[0]), comp);
    switch(cnts[0])
    {
      case 4:
        data[i].class = KIND5;
        break;
      case 3:
        data[i].class = KIND4;
        break;
      case 2:
        if(cnts[3] == 1)
        {
          data[i].class = FULL;
        }
        else
        {
          data[i].class = KIND3;
        }
        break;
      case 1:
        if(cnts[2] == 1)
        {
          data[i].class = TPAIR;
        }
        else
        {
          data[i].class = PAIR;
        }
        break;
      case 0:
        data[i].class = HIGH;
        break;
      default:
        printf("Oops!\n");
        exit(-1);
        break;
    }
  }
}

int comphand (const void * elem1, const void * elem2) 
{
  hand_t* h1 = (hand_t*)elem1;
  hand_t* h2 = (hand_t*)elem2;
  char* order = "AKQJT98765432";
    
  if (h1->class < h2->class) return  -1;  // Higher is better
  if (h1->class > h2->class) return 1;
  for(int i=0;i<5;i++)
  {
    char c1 = h1->hand[i];
    char c2 = h2->hand[i];
    char *s1 = order;
    char *s2 = order;

    while(*s1 && (*s1 != c1))
    {
      s1++;
    }
    while(*s2 && (*s2 != c2))
    {
      s2++;
    }
    if (s1 < s2) return 1;  // Lower is better
    if (s1 > s2) return -1;
  }
  return 0;
}


int main(int argc, char* argv[])
{
  unsigned long sum = 0;
  classify();
  
  qsort (data, sizeof(data)/sizeof(data[0]), sizeof(data[0]), comphand);
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    printf("Hand %i bid %i\n",i+1,data[i].bid);
    sum += ((unsigned long)(i+1))*data[i].bid;
  }
  printf("Sum: %lu\n",sum);
  return 0;
}
