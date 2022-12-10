#include <stdio.h>

const int numb[] = {90,4,2,96,46,1,62,97,3,52,7,35,50,28,31,37,74,26,59,53,82,47,83,80,19,40,68,95,34,55,54,73,12,78,30,63,57,93,72,77,56,91,23,67,64,79,85,84,76,10,58,0,29,13,94,20,32,25,11,38,89,21,98,92,42,27,14,99,24,75,86,51,22,48,9,33,49,18,70,8,87,61,39,16,66,71,5,69,15,43,88,45,6,81,60,36,44,17,41,65};

int boards[][5][5] = {
#include "input.c"
};

int main(int argc, char* argv[])
{
  int i;

  for(i=0;i<(sizeof(boards)/sizeof(boards[0]));i++)
  {
    int x;
    int y;
    int j=0;
    int won = 0;
    while(!won && j<(sizeof(numb)/sizeof(numb[0])))
    {
      int colsum[5] = {0,0,0,0,0};
      for(y=0;y<5;y++)
      {
        int rowsum=0;
        for(x=0;x<5;x++)
        {
          if(boards[i][y][x] == numb[j])
          {
            boards[i][y][x] = -1;  // -1 marker for crossed
          }
          rowsum+=boards[i][y][x];
          colsum[x]+=boards[i][y][x];
          if((rowsum == -5) || (colsum[x] == -5))
          {
            won = 1;
          }
        }
      }
      if(!won)
      {
        j++;
      }
    }
    if(won)
    {
      int sum = 0;
      for(y=0;y<5;y++)
      {
        for(x=0;x<5;x++)
        {
          if(boards[i][y][x]>0)
          {
            sum += boards[i][y][x];
          }
        }
      }
      printf("Board %i won at move %i score %i\n",i,j,numb[j]*sum);
    }
  }
  return 0;
}
