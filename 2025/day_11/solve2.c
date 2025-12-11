#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#if 0
typedef enum node_t {
#include "data3d.txt"
} node_t;

node_t coni[] = {
#include "data3c.txt"
};

char* names[] = {
#include "data3s.txt"
};
#else
typedef enum node_t {
#include "datad.txt"
} node_t;

node_t coni[] = {
#include "datac.txt"
};

char* names[] = {
#include "datas.txt"
};
#endif

node_t con[1024][32];

unsigned long paths(node_t s, node_t e)
{
  unsigned long sumpaths[1024];
  unsigned long NOTCALC = (unsigned long)-1;

  printf("Searching from %s to %s\n",names[s],names[e]);
  memset(sumpaths,-1,sizeof(sumpaths));
  sumpaths[e]=1;
  while(sumpaths[s]==NOTCALC)
  {
    for(int i=0;i<=out;i++)
    {
      int all = 1;
      unsigned long sum = 0;
      int j;

      if(sumpaths[i]==NOTCALC)
      {
        for(j=0;(j<32)&&(con[i][j]!=NOC)&&all;j++)
        {
          all = sumpaths[con[i][j]]!=NOTCALC;
          sum += sumpaths[con[i][j]];
        }
        if(all)
        {
          sumpaths[i] = sum;
        }
      }
    }
  }
  return sumpaths[s];
}

int main(int argc, char* argv[])
{
  unsigned long pathc;
  unsigned long mul;
  
  memset(con,NOC,sizeof(con));
  
  for(int i=0;i<(sizeof(coni)/sizeof(coni[0]));)
  {
    node_t* p = &coni[i+1];
    node_t idx = coni[i];
    int j=0;
    
    i++;
    printf("Connecting node %s to: ",names[idx]);
    while(*p!=NOC)
    {
      printf("%s ",names[*p]);
      con[idx][j++] = *p;
      p++;
      i++;
    }
    i++;
    printf("\n");
  }

  pathc = paths(svr,fft);
  mul = pathc;
  printf("Paths1: %lu\n",pathc);

  
  pathc = paths(fft,dac);
  mul *= pathc;
  printf("Paths2: %lu\n",pathc);

  pathc = paths(dac,out);
  mul *= pathc;
  printf("Paths3: %lu %lu\n",pathc,mul);
    
  return 0;
}
