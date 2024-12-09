#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data =  
#include "data.txt"
;

// Disksize 95177
int disk[200000];

int main(int argc, char* argv[])
{
  int len = strlen(data);
  int disksize = 0;
  int file = 1;
  int filenr = 0;
  int headpos = 0;
  
  printf("Len: %i\n",len);
  memset(disk,0,disksize);

  for(int i=0;i<len;i++)
  {
    int llen = data[i]-'0'; 
    disksize+=llen;
    for(int j=0;j<llen;j++)
    {
      if(file)
      {
        disk[headpos++] = filenr;
      }
      else
      {
        disk[headpos++] = -1;  // Empty
      } 
    }
    if(file)
    {
      filenr++;
    }
    file = !file;
  }
  if(headpos!=disksize)
  {
    printf("Ooops %i %i\n",headpos,disksize);
    exit(-1);
  }
  printf("Disksize: %i\n",disksize);

  {
    int s = 0;
    int e = disksize-1;

    do
    {
      while((disk[s]>=0) && (s<disksize))
      {
        s++;
      }
      while((disk[e]==-1) && (e))
      {
        e--;
      }
      if(s<e)
      {
        printf("Moving %i to %i\n",e,s);
        disk[s] = disk[e];
        disk[e] = -1;
        s++;
        e--;
      }
    } while(s<e);
  }

  {
    unsigned long chk = 0;
    
    for(int i=0;i<disksize;i++)
    {
      if(disk[i]>=0)
      {
        chk += i*disk[i];
      }
    }
    printf("Cheksum: %lu\n",chk);
  }

#if 0
  {
    for(int i=0;i<disksize;i++)
    {
      if(disk[i]>=0)
      {
        printf("%i",disk[i]);
      }
      else
      {
        printf(".");
      }
    }
    printf("\n");
  }
#endif
  return 0;
}
