#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
  int e1s;
  int e1p;
  int e2s;
  int e2p;
} elf_pair_t;

const elf_pair_t data[] = {
#include "data.txt"
};

int main(int argc, char* argv[])
{
  int cnt =0;

  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    int e1s = data[i].e1s ;
    int e1p = data[i].e1p ;
    int e2s = data[i].e2s ;
    int e2p = data[i].e2p ;
    
    //  ----        ----  ----   ----
    //     ----    --      ---    ---
    if(( e1s >= e2s && e1s <= e2p) || (e1p >= e2s && e1p <=e2p))
    {
      printf("%i-%i,%i-%i\n",e1s,e1p,e2s,e2p);
      cnt++;
    }
    else if (( e2s >= e1s && e2s <= e1p) || (e2p >= e1s && e2p <=e1p))
    {
      printf("%i-%i,%i-%i (o)\n",e1s,e1p,e2s,e2p);
      cnt++;
    }
  }
  printf("Cnt: %i\n",cnt);
  return 0;
}
