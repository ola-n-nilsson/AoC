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

int lengthslen[sizeof(data)/sizeof(data[0])];
int lengthssum[sizeof(data)/sizeof(data[0])];

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
      lengthssum[i] += data[i].lengths[j];
    }
    lengthslen[i] = j;
    printf("\n");
  }
  printf("\n");

  // Create all possible binary numbers with the length of the record and try them
  {
    long possum = 0;
    // Longest rec length in my data is 20
    // Max moving zeros in my data is 13
    
    for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
    {
      int reclen = strlen(data[i].rec);
      unsigned int recmask = 0;
      int wild = 0;
      int possible = 0;
      
      for(int j=reclen-1;j>=0;j--)
      {
        if(data[i].rec[j]=='?')
        {
          wild++;
        }
        recmask = recmask<<1;
        if(data[i].rec[j]=='.') // Must be zero
        {
          recmask |=1;
        }
      }

      //      printf("Must place %i ones in %i groups (%i) in space of %i. Moving zeros: %i\n",lengthssum[i],lengthslen[i],lengthssum[i]+lengthslen[i]-1, reclen, reclen - (lengthssum[i]+lengthslen[i]-1));

      // .??..??...?##. 1,1,3
      
      for(int k=0;k<(1<<wild);k++)
      {
        unsigned int try = 0;
        unsigned int thisguess = k;
        
        for(int j=reclen-1;j>=0;j--)
        {
          try = try<<1;
          if(data[i].rec[j]=='?')
          {
            try |= (thisguess&0x1);
            thisguess = thisguess>>1;
          }
          else if(data[i].rec[j]=='#')
          {
            try |= 1;
          }
        }

        {
          unsigned int ltry=try;

          for(int j=0;(j<lengthslen[i])&&ltry;j++)
          {
            int group;
            
            //Rotate away zeros
            while(!(ltry&1))
            {
              ltry = ltry>>1;
            }
            // Count group of ones
            group = 0;
            while(ltry&1)
            {
              group++;
              ltry = ltry>>1;
            }
            // at least one zero after
            ltry = ltry>>1;
            if(group == data[i].lengths[j])
            {
              if((j==(lengthslen[i]-1)) && !ltry)
              {
                possible++;
                break;
              }
            }
            else
            {
              break;
            }
          }
        }
        
      }
      printf("%i has %i possible\n",i,possible);
      possum+=possible;
    }
    printf("Sum: %li\n",possum);
  }
  
  return 0;
}
