#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

int stopidx = 0;
int charidx[256];

int possible(char* p)
{
  int c = *p;

  if(!(*p))
  {
    return 1;
  }
  if(charidx[c]==-1)
  {
    return 0;
  }
  for(int i=charidx[c];data[i][0]==c;i++)
  {
    char *s = data[i];
    char *p2 = p;
    
    while(*p2 && *s && *p2==*s)
    {
      s++;
      p2++;
    }
    if(!(*s))
    {
      if(possible(p2))
      {
        return 1;
      }
    }
  }
  return 0;
}

int main(int argc, char* argv[])
{
  int c = data[0][0];
  int cnt = 0;
  
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
    if(possible(data[i]))
    {
      cnt++;
    }
  }
  printf("Possible designs: %i\n",cnt);
  return 0;
}
