#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
  char* rec;
  int lengths[100];
} line_t;

line_t data[] = {
#include "data.txt"
};
unsigned long sum = 0;
long results[64][256];

int possible(char* mask, int length, int end)
{
  while(*mask && length)
  {
    if(*mask=='.')
    {
      return 0;
    }
    length--;
    mask++;
  }
  if(length)
  {
    return 0; // Ran out of mask.
  }
  if(end)
  {
    // No more # allowed
    while(*mask && (*mask!='#'))
    {
      mask++;
    }
    if(*mask=='#')
    {
      return 0;
    }
  }
  else
  {
    // At least one space until next length
    if(!(*mask) || (*mask=='#'))
    {
      return 0;
    }
  }
  return 1;
}

//                                                 largest in my data
//                                                 6 => 30            20 => 104
unsigned long recursetry(char* mask, int* lengths, int length_idx, int mask_idx)
{
  unsigned long ret = 0;
  
  if(!(lengths[length_idx]))
  {
    return 1;
  }
  if(results[length_idx][mask_idx]!=-1)
  {
    return results[length_idx][mask_idx];
  }
  switch(mask[mask_idx])
  {
    case '?':
      // Try # only if possible
      if(possible(&(mask[mask_idx]),lengths[length_idx],!(lengths[length_idx+1])))
      {
        ret += recursetry(mask, lengths, length_idx+1, mask_idx+lengths[length_idx]+1);
      }
      // Always try .
      ret += recursetry(mask,lengths,length_idx,mask_idx+1);
      break;
    case '#':
      if(possible(&(mask[mask_idx]),lengths[length_idx],!(lengths[length_idx+1])))
      {
        ret += recursetry(mask, lengths, length_idx+1, mask_idx+lengths[length_idx]+1);
      }
      else
      {
        // This is not possible
        break;
      }
      break;
    case '.':
      ret += recursetry(mask,lengths,length_idx,mask_idx+1);
      break;
  }

  results[length_idx][mask_idx] = ret;
  
  return ret;
}

int main(int argc, char* argv[])
{
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    int j;
    printf("%s ",data[i].rec);
    for(j=0;data[i].lengths[j];j++)
    {
      if(!j)
      {
        printf("%i",data[i].lengths[j]);
      }
      else
      {
        printf(",%i",data[i].lengths[j]);
      }
    }
    printf("\n");
  }
  printf("\n");

  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    char mask5[500];
    int len5[200];
    int llen = 0;
    int* l_p = &(data[i].lengths[0]);
    int rlen = strlen(data[i].rec);
    unsigned long ret;

    memset(results,-1,sizeof(results));
    memset(mask5,0,sizeof(mask5));
    memset(len5,0,sizeof(len5));
    while(*l_p)
    {
      llen++;
      l_p++;
    }
    if((llen>=40) || (rlen>90))
    {
      printf("Ooops\n");
      exit(-1);
    }

    for(int j=0;j<llen;j++)
    {
      len5[j] = data[i].lengths[j];
      len5[j+(1*llen)] = data[i].lengths[j];
      len5[j+(2*llen)] = data[i].lengths[j];
      len5[j+(3*llen)] = data[i].lengths[j];
      len5[j+(4*llen)] = data[i].lengths[j];
    }
    for(int j=0;j<rlen;j++)
    {
      mask5[j] = data[i].rec[j];
      mask5[j+(1*(rlen+1))] = data[i].rec[j];
      mask5[j+(2*(rlen+1))] = data[i].rec[j];
      mask5[j+(3*(rlen+1))] = data[i].rec[j];
      mask5[j+(4*(rlen+1))] = data[i].rec[j];
    }
    mask5[1*rlen] = '?';
    mask5[2*rlen+1] = '?';
    mask5[3*rlen+2] = '?';
    mask5[4*rlen+3] = '?';
    
    ret = recursetry(mask5,&(len5[0]),0,0);
    sum += ret;

    printf("%i has %lu possible\n",i,ret);
  }

  printf("\nSum: %lu\n",sum);
}

