#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int data[][20] = {
#include "data.txt"
};

int try(int* p)
{
  int j=1;
  int ok = 1;
  int dir = 0;
  int ret = 0;
  
  while(p[j]>=0)
  {
    int curdir = p[j]-p[j-1];
    if(j==1)
    {
      dir = curdir;
    }
    if(!curdir || (abs(curdir)>3))
    {
      ok=0;
      break;
    }
    if((curdir>0 && dir<0)||(curdir<0 && dir>0))
    {
      ok=0;
      break;
    }
    j++;
  }
  if(ok)
  {
    ret++;
  }
  return ret;
}

int trywithout(int* p)
{
  int without[100];
  int idx = 0;
  
  for(int x=0;p[x]>0;x++)
  {
    for(int j=0;p[j]>0;j++)
    {
      if(j!=x)
      {
        without[idx++] = p[j];
      }
    }
    without[idx] = -1;
    if(try(&without[0]))
    {
      return 1;
    }
    idx = 0;
  }
  return 0;
}

int main(int argc, char* argv[])
{
  int i=0;
  int cnt = 0;
  int ok;
  
  while(data[i][0]>=0)
  {
    if((ok = try(data[i])))
    {
      cnt++;
    }
    else if ((ok = trywithout(data[i])))
    {
      cnt++;
    }
    printf("Row: %i is %s\n",i+1,ok?"ok":"nok");
    i++;
  }
  printf("Reports ok: %i\n",cnt);
  return 0;
}
