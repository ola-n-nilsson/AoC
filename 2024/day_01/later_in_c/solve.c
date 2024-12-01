#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

const int data[] = {
#include "data.txt"
};

const int rlen = (sizeof(data)/sizeof(data[0]))/2;

int range1[2000];
int range2[2000];

int compare(const void* a, const void* b)
{
   return (*(int*)a - *(int*)b);
}

int main(int argc, char* argv[])
{
  for(int i=0;i<rlen;i++)
  {
    range1[i] = data[i*2];
    range2[i] = data[i*2+1];
  }
  qsort(range1, rlen, sizeof(int), compare);
  qsort(range2, rlen, sizeof(int), compare);

  //part 1
  {
    unsigned long distsum = 0;
    for(int i=0;i<rlen;i++)
    {
      distsum += abs(range1[i]-range2[i]);
    }
    printf("Part1: %lu\n",distsum);
  }

  //part 2
  {
    unsigned long distsum = 0;
    for(int i=0;i<rlen;i++)
    {
      unsigned int cnt=0;
      //LMF, binsearch and count...
      for(int j=0;j<rlen;j++)
      {
        if(range1[i]==range2[j])
        {
          cnt++;
        }
      }
      distsum += cnt*range1[i];
    }
    printf("Part2: %lu\n",distsum);
  }
  
  return 0;
}
