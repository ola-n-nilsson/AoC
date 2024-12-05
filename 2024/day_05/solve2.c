#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int data[] = {
#include "data.txt"
};

int rulesend = 0;

int main(int argc, char* argv[])
{
  int printcnt = 0;
  int sum = 0;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=2)
  {
    if((data[i]==-1) && (data[i+1]==-1))
    {
      rulesend = i;
      break;
    }
  }
  // Start with simple search back for breaking rules
  for(int j=rulesend+2;j<(sizeof(data)/sizeof(data[0]));)
  {
    int printstart = j;
    int printend = 0;
    int i = j;
    int moved = 0;
    int lastmoved;
    
    printcnt++;
    while(data[i]!=-1)
    {
      i++;
    }
    printend = i;

    do
    {
      lastmoved = moved;
      for(i=printstart+1;i<printend;i++)
      {
        //For all rules search back
        for(int ri=0;ri<rulesend;ri+=2)
        {
          if(data[ri]<data[i])
          {
            continue;
          }
          else if(data[ri]==data[i])
          {
            for(int bi=i-1;bi>=printstart;bi--)
            {
              if(data[bi]==data[ri+1])
              {
                int m = data[bi];
                data[bi] = data[i];
                data[i] = m;
                moved++;
                break;
              }
            }
          }
          else
          {
            //Rules sorted.
            break;
          }
        }
      }
    } while(moved!=lastmoved);

    if(moved)
    {
      sum += data[printstart + ((printend-printstart)/2)];
    }
    printf("Print %i: moved %i (sum %i)\n",printcnt,moved,sum);
    j=printend+1;
  }
  
  return 0;
}
