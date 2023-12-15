#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data = {
#include "data.txt"
};

int hash(char* s,char* e)
{
  int h = 0;

  while(s!=e)
  {
    h += *s;
    h *=17;
    h = h&0xFF;
    s++;
  }
  return h;
}
int main(int argc, char* argv[])
{
  char* cur_p = data;
  char* start_p;
  int h;
  int cnt = 1;
  unsigned long sum = 0;
  do
  {
    start_p = cur_p;
    while(*cur_p && *cur_p!=',')
    {
      cur_p++;
    }
    h = hash(start_p,cur_p);
    printf("Hash %i: %i\n",cnt++,h);
    sum += h;
    if(*cur_p)
    {
      cur_p++;
    }
  } while(*cur_p);

  printf("Sum: %lu\n",sum);
        
  return 0;
}
