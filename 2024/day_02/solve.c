#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int data[][20] = {
#include "data.txt"
};

int main(int argc, char* argv[])
{
  int i=0;
  int cnt = 0;
  
  while(data[i][0]>=0)
  {
    int j=1;
    int ok = 1;
    int dir = 0;
    
    while(data[i][j]>=0)
    {
      int curdir = data[i][j]-data[i][j-1];
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
      cnt++;
    }
    printf("Row: %i is %s\n",i+1,ok?"ok":"nok");
    i++;
  }
  printf("Reports ok: %i\n",cnt);
  return 0;
}
