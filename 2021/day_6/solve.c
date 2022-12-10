#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const unsigned char start_data[] = { 4,1,4,1,3,3,1,4,3,3,2,1,1,3,5,1,3,5,2,5,1,5,5,1,3,2,5,3,1,3,4,2,3,2,3,3,2,1,5,4,1,1,1,2,1,4,4,4,2,1,2,1,5,1,5,1,2,1,4,4,5,3,3,4,1,4,4,2,1,4,4,3,5,2,5,4,1,5,1,1,1,4,5,3,4,3,4,2,2,2,2,4,5,3,5,2,4,2,3,4,1,4,4,1,4,5,3,4,2,2,2,4,3,3,3,3,4,2,1,2,5,5,3,2,3,5,5,5,4,4,5,5,4,3,4,1,5,1,3,4,4,1,3,1,3,1,1,2,4,5,3,1,2,4,3,3,5,4,4,5,4,1,3,1,1,4,4,4,4,3,4,3,1,4,5,1,2,4,3,5,1,1,2,1,1,5,4,2,1,5,4,5,2,4,4,1,5,2,2,5,3,3,2,3,1,5,5,5,4,3,1,1,5,1,4,5,2,1,3,1,2,4,4,1,1,2,5,3,1,5,2,4,5,1,2,3,1,2,2,1,2,2,1,4,1,3,4,2,1,1,5,4,1,5,4,4,3,1,3,3,1,1,3,3,4,2,3,4,2,3,1,4,1,5,3,1,1,5,3,2,3,5,1,3,1,1,3,5,1,5,1,1,3,1,1,1,1,3,3,1};

unsigned long realloc_data(unsigned char** data_pp, unsigned long cursize)
{
  unsigned long newsize = cursize*2;
  unsigned char* newdata = malloc(newsize);
  memset(newdata, 0, newsize);
  memcpy(newdata,*data_pp,cursize);
  free(*data_pp);
  *data_pp = newdata;
  return newsize;
}

int main(int argc, char* argv[])
{
  unsigned long cursize = 1024*1024*sizeof(unsigned char);
  unsigned char* data = malloc(cursize);
  unsigned long curidx = sizeof(start_data)/sizeof(start_data[0]);
  
  memset(data,0,cursize);
  memcpy(data,start_data,sizeof(start_data));

  for(int day=0;day<80;day++)
  {
    if(curidx*2 > cursize)
    {
      //Heuristic realloc...
      cursize = realloc_data(&data,cursize);
      printf("ola: realloc %lu\n",cursize);
    }
    unsigned long dayidx = curidx;
    for(unsigned long i=0;i<dayidx;i++)
    {
      if(!data[i])
      {
        data[i] = 6;
        data[curidx++] = 8;
      }
      else
      {
        data[i]--;
      }
    }
    printf("day: %i pop: %lu\n",day+1,curidx);
  }
  
  return 0;
}
