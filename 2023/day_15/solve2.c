#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data = {
#include "data.txt"
};

char hashmapl[256][5000][10];
int hashmapv[256][5000];
int hashmapidx[256];

void printhash(void)
{
  for(int h=0;h<256;h++)
  {
    int i=0;

    for(i=0;i<hashmapidx[h];i++)
    {
      if(!i)
      {
        printf("Box %i: [%s %i]",h,hashmapl[h][i],hashmapv[h][i]);
      }
      else
      {
        printf(" [%s %i]",hashmapl[h][i],hashmapv[h][i]);
      }
    }
    if(i)
      printf("\n");
  }
}

void hashadd(int h, char* label,int op)
{
  int i;
  
  for(i=0;i<hashmapidx[h];i++)
  {
    if(!strcmp(label,hashmapl[h][i]))
    {
      hashmapv[h][i] = op;
      return;
    }
  }
  printf("Will add %i %s %i\n",h,label,op);
  strcpy(hashmapl[h][i],label);
  hashmapv[h][i] = op;
  hashmapidx[h]++;
}

void hashrm(int h,char* label)
{
  for(int i=0;i<hashmapidx[h];i++)
  {
    if(!strcmp(label,hashmapl[h][i]))
    {
      printf("Will remove %i %s\n",h,label);
      for(int j=i;j<hashmapidx[h];j++)
      {
        strcpy(hashmapl[h][j],hashmapl[h][j+1]);
      }
      memcpy(&hashmapv[h][i],&hashmapv[h][i+1],sizeof(int)*(hashmapidx[h]-i));
      hashmapidx[h]--;
      printf("Removed!\n");
      break;
    }
  }
}

unsigned long sumhash(void)
{
  unsigned long sum = 0;

  for(int h=0;h<256;h++)
  {
    for(int i=0;i<hashmapidx[h];i++)
    {
      sum+= (h+1) * (i+1) * hashmapv[h][i];
    }
  }
  return sum;
}

int hash2(char* s)
{
  int h = 0;

  while(*s)
  {
    h += *s;
    h *=17;
    h = h&0xFF;
    s++;
  }
  return h;
}



int main(int argc, char* argv[])
{
  char* cur_p = data;
  char* op_p;
  int h;
  unsigned long sum = 0;

  memset(hashmapl,0,sizeof(hashmapl));
  memset(hashmapv,0,sizeof(hashmapv));
  memset(hashmapidx,0,sizeof(hashmapidx));
  
  do
  {
    int op = 0;
    char label[10];
    int lidx = 0;
    
    while(*cur_p && *cur_p!='-' && *cur_p!='=')
    {
      label[lidx++] = *cur_p;
      cur_p++;
    }
    label[lidx] = 0;
    h = hash2(label);
    op_p=cur_p;
    cur_p++;
    while(*cur_p && *cur_p!=',')
    {
      if(*cur_p>='0' && *cur_p<='9')
      {
        op*=10;
        op+=*cur_p-'0';
      }
      cur_p++;
    }
    if(*op_p=='=')
    {
      hashadd(h,label,op);
    }
    else
    {
      hashrm(h,label);
    }
    if(*cur_p)
    {
      cur_p++;
    }
  } while(*cur_p);

  sum = sumhash();
  printf("Sum: %lu\n",sum);
  
  return 0;
}
