#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

int stopidx = 0;
int charidx[256];

unsigned long cache[200];
unsigned long hits = 0;

unsigned long possible(char* p, int pos)
{
  unsigned long ret = 0;
  int c = *p;

  if(cache[pos]!=(unsigned long)-1)
  {
    hits++;
    return cache[pos];
  }
  
  if(!(*p))
  {
    cache[pos] = 1;
    return 1;
  }
  if(charidx[c]==-1)
  {
    cache[pos] = 0;
    return 0;
  }
  for(int i=charidx[c];data[i][0]==c;i++)
  {
    char *s = data[i];
    char *p2 = p;
    int pos2 = pos;
    
    while(*p2 && *s && *p2==*s)
    {
      s++;
      p2++;
      pos2++;
    }
    if(!(*s))
    {
      ret += possible(p2,pos2);
    }
  }
  cache[pos] = ret;
  return ret;
}

int main(int argc, char* argv[])
{
  int c = data[0][0];
  unsigned long sum = 0;
  
  memset(charidx,-1,sizeof(charidx));
  charidx[c] = 0;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    if(!stopidx && data[i][0]!=c)
    {
      c = data[i][0];
      charidx[c] = i;
    }
    if(!strlen(data[i]))
    {
      stopidx = i;
      break;
    }
  }

  for(int i=stopidx+1;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    memset(cache,-1,sizeof(cache));
    sum += possible(data[i],0);
  }
  printf("Possible designs sum: %lu (hits %lu)\n",sum,hits);
  return 0;
}
