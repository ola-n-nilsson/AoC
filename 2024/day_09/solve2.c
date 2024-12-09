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
    
    while(filenr)
    {
      int e = disksize-1;
      int len = 0;
      int slen = 0;
      int sidx = 0;
      int s = 0;
      
      filenr--;
      while(disk[e]!=filenr)
      {
        e--;
      }
      while((disk[e]==filenr) && e)
      {
        e--;
        len++;
      }
      if(e)
      {
        e++;
      }
      do
      {
        sidx = s;
        slen = 0;
        while((disk[s]!=-1) && (s<e))
        {
          s++;
        }
        sidx = s;
        while((disk[s]==-1) && (s<e))
        {
          s++;
          slen++;
        }
      } while((slen<len) && (s<e));

      if((s<disksize) && (slen>=len))
      {
        //printf("Moving %i from %i to %i (space %i len %i)\n",filenr,e,sidx,slen,len);
        for(int j=0;j<len;j++)
        {
          disk[sidx+j] = disk[e+j];
          disk[e+j] = -1;
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

      }
    }
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
