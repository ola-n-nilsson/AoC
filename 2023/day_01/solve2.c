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
  char* nbrs[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    char* s = data[i];
    unsigned int nbr = 0;
    int digitf = 0;
    int digitl = 0;
    int found = 0;
    int digitfpos = 0;
    int digitlpos = strlen(data[i]);
    
    for(int j=0;j<strlen(data[i]);j++)
    {
      if(s[j]>='0' &&  s[j]<='9')
      {
        if(found==0)
        {
          digitf = s[j] - '0';
          digitfpos = j;
        }
        found++;
        digitl = s[j] - '0';
        digitlpos = j;
      }
    }
    for(int j=0;j<(sizeof(nbrs)/sizeof(nbrs[0]));j++)
    {
      char* t;
      char* lastt;
      t = strstr(s,nbrs[j]);
      if(t)
      {
        int pos = t - s;
        if(pos<digitfpos)
        {
          digitf = j+1;
          digitfpos = pos;
        }

        // Now the last
        do
        {
          lastt = t;
          t = strstr(t+1,nbrs[j]);
        } while (t);

        pos = lastt - s;
        if(pos>digitlpos)
        {
          digitl = j+1;
          digitlpos = pos;
        }


      }
    }
    nbr = (digitf*10) + digitl;
    //    printf("Found: %u\n",nbr);
    sum += nbr;
  }
  printf("Sum: %u\n",sum);
  return 0;
}

