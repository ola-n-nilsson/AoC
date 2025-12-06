#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "datab.txt"
};

unsigned long helper(int start, int end)
{
  unsigned long ret = 0;
  unsigned long nbrs[20];
  int nbr_idx = 0;

  if((end-start)>15)
  {
    printf("Oops\n");
    exit(-1);
  }
  
  printf("Startend: %i %i\n",start,end);

  for(int i=end;i>=start;i--)
  {
    unsigned long nbr = 0;

    for(int j=0;j<4;j++)
    {
      if(data[j][i]!=' ')
      {
        nbr*=10;
        nbr += (data[j][i]-'0');
      }
    }
    nbrs[nbr_idx++]=nbr;
  }
  
  if(data[4][start]=='+')
  {
    for(int i=0;i<nbr_idx;i++)
    {
      printf("Adding %lu\n",nbrs[i]);
      ret += nbrs[i];
    }
  }
  else if(data[4][start]=='*')
  {
    ret = 1;
    for(int i=0;i<nbr_idx;i++)
    {
      printf("Muling %lu\n",nbrs[i]);
      ret *= nbrs[i];
    }
  }
  else
  {
    printf("No op at %i\n",start);
    exit(-1);
  }
  printf("Result: %lu\n",ret);
  return ret;
}

int main(int argc, char* argv[])
{
  unsigned long sum = 0;
  int dividers[1028];
  int divpos = 0;
  
  for(int i=0;i<(strlen(data[0]));i++)
  {
    if(data[0][i]==' ' &&
       data[1][i]==' ' &&
       data[2][i]==' ' &&
       data[3][i]==' ' &&
       data[4][i]==' ')
    {
      printf("Found divider at %i\n",i);
      dividers[divpos++] = i;
    }
  }
  printf("Found %i dividers\n",divpos);
  for(int i=0;i<=divpos;i++)
  {
    unsigned long ret;

    if(!i)
    {
      ret = helper(0,dividers[i]-1);
    }
    else if(i==divpos)
    {
      ret = helper(dividers[i-1]+1,strlen(data[0])-1);
    }
    else
    {
      ret = helper(dividers[i-1]+1,dividers[i]-1);
    }
    sum += ret;
  }

  printf("Sum: %lu\n",sum);
  return 0;
}
