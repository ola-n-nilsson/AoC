#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>


/*         [H]         [S]         [D] */
/*     [S] [C]         [C]     [Q] [L] */
/*     [C] [R] [Z]     [R]     [H] [Z] */
/*     [G] [N] [H] [S] [B]     [R] [F] */
/* [D] [T] [Q] [F] [Q] [Z]     [Z] [N] */
/* [Z] [W] [F] [N] [F] [W] [J] [V] [G] */
/* [T] [R] [B] [C] [L] [P] [F] [L] [H] */
/* [H] [Q] [P] [L] [G] [V] [Z] [D] [B] */
/*  1   2   3   4   5   6   7   8   9  */


char stacks[10][80];

void PrintAll()
{
  for(int i=1;i<10;i++)
  {
    printf("%i: ",i);
    for(int j=0;j<80;j++)
    {
      if(stacks[i][j])
      {
        printf("%c",stacks[i][j]);
      }
      else
      {
        printf("\n");
        break;
      }
    }
  }
  
}

typedef struct {
  int cnt;
  int from;
  int to;
}  move_t;

const move_t data[] = {
  #include "data.txt"

   /* {1,2,1}, */
   /* {3,1,3}, */
   /* {2,2,1}, */
   /* {1,1,2}, */
};

int main(int argc, char* argv[])
{

  memset(stacks,0,sizeof(stacks));
  stacks[1][0]='H';
  stacks[1][1]='T';
  stacks[1][2]='Z';
  stacks[1][3]='D';

  stacks[2][0]='Q';
  stacks[2][1]='R';
  stacks[2][2]='W';
  stacks[2][3]='T';
  stacks[2][4]='G';
  stacks[2][5]='C';
  stacks[2][6]='S';

  stacks[3][0]='P';
  stacks[3][1]='B';
  stacks[3][2]='F';
  stacks[3][3]='Q';
  stacks[3][4]='N';
  stacks[3][5]='R';
  stacks[3][6]='C';
  stacks[3][7]='H';

  stacks[4][0]='L';
  stacks[4][1]='C';
  stacks[4][2]='N';
  stacks[4][3]='F';
  stacks[4][4]='H';
  stacks[4][5]='Z';
  
  stacks[5][0]='G';
  stacks[5][1]='L';
  stacks[5][2]='F';
  stacks[5][3]='Q';
  stacks[5][4]='S';

  stacks[6][0]='V';
  stacks[6][1]='P';
  stacks[6][2]='W';
  stacks[6][3]='Z';
  stacks[6][4]='B';
  stacks[6][5]='R';
  stacks[6][6]='C';
  stacks[6][7]='S';

  stacks[7][0]='Z';
  stacks[7][1]='F';
  stacks[7][2]='J';

  stacks[8][0]='D';
  stacks[8][1]='L';
  stacks[8][2]='V';
  stacks[8][3]='Z';
  stacks[8][4]='R';
  stacks[8][5]='H';
  stacks[8][6]='Q';

  stacks[9][0]='B';
  stacks[9][1]='H';
  stacks[9][2]='G';
  stacks[9][3]='N';
  stacks[9][4]='F';
  stacks[9][5]='Z';
  stacks[9][6]='L';
  stacks[9][7]='D';

  /* memset(stacks,0,sizeof(stacks)); */

  /* stacks[1][0]='Z'; */
  /* stacks[1][1]='N'; */

  /* stacks[2][0]='M'; */
  /* stacks[2][1]='C'; */
  /* stacks[2][2]='D'; */

  /* stacks[3][0]='P'; */

  PrintAll();
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    char toc[80];
    char fromc[80];
    int lent;
    int lenf;
    
    int cnt = data[i].cnt;
    char* to = stacks[data[i].to];
    char* from = stacks[data[i].from];

    memcpy(toc,to,80);
    memcpy(fromc,from,80);
    lent = strlen(toc);
    lenf = strlen(fromc);

    printf("move %i from %i to %i\n",cnt,data[i].from,data[i].to);
    
    if((lenf<cnt) || ((cnt+lent)>80))
    {
      printf("Oops\n");
      exit(-1);
    }

    //    strcpy(&toc[lent],&fromc[lenf-cnt]);
    int k = lent+cnt-1;
    for(int j=lenf-cnt;j<lenf;j++,k--)
    {
      toc[k] = fromc[j];
    }
    memset(&fromc[lenf-cnt],0,80-(lenf-cnt));

    memcpy(stacks[data[i].to],toc,80);
    memcpy(stacks[data[i].from],fromc,80);
    PrintAll();

  }

  PrintAll();
  return 0;
}
