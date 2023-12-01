#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

int main(int argc, char* argv[])
{
  unsigned int sum = 0;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    char* s = data[i];
    unsigned int nbr = 0;
    int digitf = 0;
    int digitl = 0;
    int found = 0;
    
    for(int j=0;j<strlen(data[i]);j++)
    {
      if(s[j]>='0' &&  s[j]<='9')
      {
        if(found==0)
        {
          digitf = s[j] - '0';
        }
        found++;
        digitl = s[j] - '0';
      }
    }
    nbr = (digitf*10) + digitl;
    //    printf("Found: %u\n",nbr);
    sum += nbr;
  }
  printf("Sum: %u\n",sum);
  return 0;
}

