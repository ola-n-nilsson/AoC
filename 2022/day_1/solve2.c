#include <stdio.h>

const int calories[] = {
#include "data1.c"
};

int main(int argc, char* argv[])
{
  int sum=0;
  int max_sum=0;
  
  for(int i=0;i<(sizeof(calories)/sizeof(calories[0]));i++)
  {
    if(calories[i]==-1)
    {
      //new elf
      if(sum>max_sum)
      {
        max_sum = sum;
      }
      printf("%i\n",sum);
      sum=0;
    }
    else
    {
      sum+=calories[i];
    }
  }

}
