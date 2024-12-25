#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

int keys[500][5];
int kidx = 0;
int locks[500][5];
int lidx = 0;

void convert(int i)
{
  int val[5] = {0,0,0,0,0};
  int key = data[i][0]=='#' &&
    data[i][1]=='#' &&
    data[i][2]=='#' &&
    data[i][3]=='#' &&
    data[i][4]=='#';
  int lock = data[i+6][0]=='#' &&
    data[i+6][1]=='#' &&
    data[i+6][2]=='#' &&
    data[i+6][3]=='#' &&
    data[i+6][4]=='#';

  if(lock)
  {
    for(int j=5;j>=0;j--)
    {
      val[0]+=data[i+j][0]=='#'?1:0;
      val[1]+=data[i+j][1]=='#'?1:0;
      val[2]+=data[i+j][2]=='#'?1:0;
      val[3]+=data[i+j][3]=='#'?1:0;
      val[4]+=data[i+j][4]=='#'?1:0;
    }
    printf("Lock: %i,%i,%i,%i,%i\n",val[0],val[1],val[2],val[3],val[4]);
    memcpy(locks[lidx],val,sizeof(val));
    lidx++;
  }
  else if(key)
  {
    for(int j=1;j<7;j++)
    {
      val[0]+=data[i+j][0]=='#'?1:0;
      val[1]+=data[i+j][1]=='#'?1:0;
      val[2]+=data[i+j][2]=='#'?1:0;
      val[3]+=data[i+j][3]=='#'?1:0;
      val[4]+=data[i+j][4]=='#'?1:0;
    }
    printf("Key: %i,%i,%i,%i,%i\n",val[0],val[1],val[2],val[3],val[4]);
    memcpy(keys[kidx],val,sizeof(val));
    kidx++;
  }
  else
  {
    printf("Ooops!\n");
    exit(-1);
  }
}

int try(int k, int l)
{
  int ret = 1;

  for(int pos=0;pos<5 && ret;pos++)
  {
    ret = keys[k][pos]+locks[l][pos]<6;
  }
  
  return ret;
}

int main(int argc, char* argv[])
{
  int cnt = 0;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=8)
  {
    convert(i);
  }
  printf("Trying %i keys in %i locks\n",kidx,lidx);
  for(int k=0;k<kidx;k++)
  {
    for(int l=0;l<lidx;l++)
    {
      if(try(k,l))
      {
        cnt++;
        printf("Key %i fits in lock %i\n",k,l);
      }
    }
  }
  printf("Fits: %i\n",cnt);
  return 0;
}


