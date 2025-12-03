#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

#define WANTED (12)

unsigned long mypow(int exp)
{
  static unsigned long pcache[WANTED];
  unsigned long val=1;
  
  if(pcache[exp])
  {
    return pcache[exp];
  }
  while(exp)
  {
    val *=10;
    exp--;
  }
  pcache[exp] = val;
  return pcache[exp];
}

unsigned long cache[128][16];
int len;
#define NOTPOS ((unsigned long)-1)

unsigned long getnbr(char* buf, int pos,int digits)
{
  unsigned long val = 0;
  
  if(cache[pos][digits]!=0)
  {
    return cache[pos][digits];
  }

  if(pos==len)
  {
    val = NOTPOS;
  }
  else if(digits==1) // We want the higest digit in the remaining buffer
  {
    int best = -1;

    for(int ii=pos;ii<len;ii++)
    {
      if((buf[ii]-'0')>best)
      {
        best = buf[ii]-'0';
      }
      if(best==9)
      {
        break;
      }
    }
    val = (unsigned long)best;
  }
  else
  {
    unsigned long valc = 0;

    if(pos<len)
    {
      val = getnbr(buf,pos+1,digits); //Don't include this digit
      valc = getnbr(buf,pos+1,digits-1); //Include this digit and get the number for the rest.
      if(valc!=NOTPOS)
      {
        valc += mypow(digits-1)*(buf[pos]-'0');
      }
      if((val!=NOTPOS && valc!=NOTPOS && (valc>val)) || (val==NOTPOS))
      {
        val = valc;
      }
    }
    else
    {
      printf("Oops!\n");
      exit(-1);
    }
  }
  
  cache[pos][digits] = val;
  return val;
}

int main(int argc, char* argv[])
{
  unsigned long sum = 0;

  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    unsigned long val;

    len = strlen(data[0]);
    memset(cache,0,sizeof(cache));
    val = getnbr(data[i],0,WANTED);
    printf("%i got %lu\n",i,val);
    sum += val;
  }
  printf("Sum: %lu\n",sum);
  return 0;
}


