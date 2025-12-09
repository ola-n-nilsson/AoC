#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

const int data[] = {
#include "data.txt"
};

int main(int argc, char* argv[])
{
  unsigned long marea = 0;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=2)
  {
    for(int j=0;j<(sizeof(data)/sizeof(data[0]));j+=2)
    {
      if(j!=i)
      {
        unsigned long xdiff = data[i] > data[j] ? (data[i]-data[j]) : (data[j]-data[i]);
        unsigned long ydiff = data[i+1] > data[j+1] ? (data[i+1]-data[j+1]) : (data[j+1]-data[i+1]);
        unsigned long area = (xdiff+1)*(ydiff+1);
        
        if(area>marea)
        {
          marea = area;
        }
      }
    }
  }
  printf("Max area: %lu\n",marea);
  return 0;
}
