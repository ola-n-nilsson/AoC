#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#if 0
const int datalen = 6;
const long data[][6] = {
#include "data2.txt"
};
#else
const int datalen = 21;
const long data[][21] = {
#include "data.txt"
};
#endif

long diffcalc[100][100];

int main(int argc, char* argv[])
{
  long sum = 0;
  int deepest = 0;
  int deepat = 0;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    int rowmax = 1;
    int rowmin = 0;
    int row = 1;
    int rowlen = datalen;
    int maxy;
    
    memset(diffcalc[0],0,sizeof(diffcalc));
    memcpy(diffcalc[0],data[i],sizeof(long)*rowlen);

    while(rowmax || rowmin)
    {
      rowmax = 0;
      rowmin = 0;
      rowlen--;
      if(!rowlen)
      {
        printf("Oops!\n");
        exit(-1);
      }
      for(int j=0;j<rowlen;j++)
      {
        diffcalc[row][j]=diffcalc[row-1][j+1] - diffcalc[row-1][j];
        if(diffcalc[row][j] > rowmax)
        {
          rowmax = diffcalc[row][j];
        }
        if(diffcalc[row][j] < rowmin)
        {
          rowmin = diffcalc[row][j];
        }
      }
      row++;
      if(row==100)
      {
        printf("Oops2!\n");
        exit(-1);
      }
    }
    // calculate backwards
    maxy = row;
    if(diffcalc[row-1][rowlen])
    {
      printf("Oops3!\n");
      exit(-1);
    }
    row--;
    if(row>deepest)
    {
      deepest = row;
      deepat = i;
    }
    while(row)
    {
      rowlen++;
      row--;
      //      printf("Row: %i len %i\n",row,rowlen);
      diffcalc[row][rowlen] = diffcalc[row+1][rowlen-1] + diffcalc[row][rowlen-1];
      if(!row)
      {
        printf("For %i new, %li\n",i,diffcalc[0][rowlen]);
        sum += diffcalc[0][rowlen];
      }
    }
    if(i==300)
    {
      for(int y=0;y<maxy;y++)
      {
        for(int x=0;x<=datalen;x++)
        {
          printf("%li\t",diffcalc[y][x]);
        }
        printf("\n");
      }
    }
  }
  printf("Deepest: %i at %i\n",deepest, deepat);

  printf("Sum: %li\n",sum);
  return 0;
}

// 1731106418 too high  Because a sum of 0 is not the same as all values in line beeing 0.
// 1731106378
