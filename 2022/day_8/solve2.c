#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

const char* data[] = {
#include "data.txt"
};

#define MAXGRID 99

int main(int argc, char* argv[])
{
  int visible = 0;
  unsigned long max_score = 0;

  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    for(int j=0;j<strlen(data[i]);j++)
    {
      if(i==0 || j==0 || j==(MAXGRID-1) || i==(MAXGRID-1))
      {
        visible++;
      }
      else
      {
        int search_hidden = 0;
        int y,x;
        unsigned long score_up=0;
        unsigned long score_down=0;
        unsigned long score_right=0;
        unsigned long score_left=0;
        
        printf("Searching: %i %i\n",i,j);

        //up
        for(y=i-1;y>=0;y--)
        {
          if(data[y][j]>=data[i][j])
          {
            score_up++;
            printf("Hidden up: %i %i\n",i,j);
            search_hidden++;
            break;
          }
          else
          {
            score_up++;
          }
        }
        //down
        for(y=i+1;(y<MAXGRID) ;y++)
        {
          if(data[y][j]>=data[i][j])
          {
            score_down++;
            printf("Hidden down: %i %i\n",i,j);
            search_hidden++;
            break;
          }
          else
          {
            score_down++;
          }
        }
        //left
        for(x=j-1;(x>=0) ;x--)
        {
          if(data[i][x]>=data[i][j])
          {
            score_left++;
            printf("Hidden left: %i %i\n",i,j);
            search_hidden++;
            break;
          }
          else
          {
            score_left++;
          }
        }
        //right
        for(x=j+1;(x<MAXGRID) ;x++)
        {
          if(data[i][x]>=data[i][j])
          {
            score_right++;
            printf("Hidden right: %i %i\n",i,j);
            //            printf("Hidden right by: %i %i\n",i,x);
            search_hidden++;
            break;
          }
          else
          {
            score_right++;
          }
        }

        {
          unsigned long score = score_right * score_left * score_up * score_down;

          if(score>max_score)
          {
            max_score = score;
          }
        }
      }
    }
  }
  printf("Visible: %i\n",visible);
  printf("Max score: %lu\n",max_score);
  return 0;
}
