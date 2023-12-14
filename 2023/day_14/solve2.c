#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

char field[110][110];
int maxy;
int maxx;

// Should just have calculated the load and found the loop. No need to keep boards.
const int oldnbr = 100;
char oldfields[100][110][110];
int oldidx;

int compto(int oldcompidx)
{
  for(int y=0;y<maxy;y++)
  {
    if(strcmp(field[y],oldfields[oldcompidx][y]))
    {
      return 0;
    }
  }

  return 1;
}

int main(int argc, char* argv[])
{
  maxy = sizeof(data)/sizeof(data[0]);
  maxx = strlen(data[0]);
  int move;
  int deltay[4] = {-1,  0, 1, 0};
  int deltax[4] = { 0, -1, 0, 1};
  
  printf("Max %i:%i\n",maxy,maxx);
  for(int y=0;y<maxy;y++)
  {
    strcpy(field[y],data[y]);
  }

  // for(long j=0;j<1000000000;j++)
  for(long j=0;j<(2*oldnbr);j++)
  {
    if(!(j%1000000))
    {
      printf("%li cycles\n",j);
    }
    for(int i=0;i<4;i++)
    {
      move = 1;
      
      while(move)
      {
        move = 0;
        for(int y=0;y<maxy;y++)
        {
          for(int x=0;x<maxx;x++)
          {
            if(field[y][x]=='O')
            {
              int diry = y+deltay[i];
              int dirx = x+deltax[i];

              if(deltay[i])
              {
                if((diry>-1) && (diry<maxy) && field[diry][x] == '.')
                {
                  field[diry][x] = 'O';
                  field[y][x] = '.';  //Always . below O
                  move=1;
                }
              }
              else
              {
                if((dirx>-1) && (dirx<maxx) && field[y][dirx] == '.')
                {
                  field[y][dirx] = 'O';
                  field[y][x] = '.';  //Always . below O
                  move=1;
                }
              }
            }
          }
        }
      }
    }


    {
      unsigned long load = 0;
      for(int y=0;y<maxy;y++)
      {
        for(int x=0;x<maxx;x++)
        {
          //          printf("%c",field[y][x]);
          if(field[y][x]=='O')
          {
            load += (maxy-y);
          }
        }
        //        printf("\n");
      }
      printf("Load: %lu Cycles: %li\n",load,j+1);
    }

    
    if(oldidx>oldnbr)
    {
      //find
      for(int k=0;k<oldnbr;k++)
      {
        if(compto((oldidx-k)%oldnbr))
        {
          unsigned long target = 1000000000 - j - 1;
          
          printf("Loop period: %i. %li moves in.\n",k,j+1);
          if(!(target % (k)))
          {
            printf("This seems like the place to stop!\n");
            // Lazy, but the right answer is at the end of output just above the last "place to stop"...
          }
          break;
        }
      }
    }
    memcpy(oldfields[oldidx%oldnbr],field,sizeof(field));
    oldidx++;
  }
  
  return 0;
}


