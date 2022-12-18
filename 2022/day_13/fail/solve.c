#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

char* data[] = {
#include "data2b.txt"
};

#define MAX_VEC 4096

int* parse(char** pp,int* level_p,char** first_comma_pp)
{
  int* vector = malloc(sizeof(int)*MAX_VEC);
  int idx = 0;
  *first_comma_pp = NULL;
  int empty = 0;
  int loclev=0;
  *level_p = 0;
  
  while(!isdigit(**pp) && **pp)
  {
    //    printf("Ola1: %c\n",**pp);
    if(**pp=='[')
    {
      loclev++;
      (*level_p)++;
      (*pp)++;
    }
    else if(**pp==']')
    {
      // Empty something;
      (*pp)++;
      empty = 1;
      if(loclev)
        loclev--;
      break;
    }
    else
    {
      printf("Oops: %c (%s)\n",**pp,*pp);
      exit(-1);
    }
  }
  if(!empty)
  {
    while(isdigit(**pp) && **pp)
    {
      //      printf("Ola2: %s\n",*pp);
      
      //Get number
      if(sscanf(*pp, "%i",&vector[idx]) == 1)
      {
        idx++;
        while(isdigit(**pp))
        {
          (*pp)++;
        }
      }
      if(**pp==',')
      {
        if(!*first_comma_pp)
        {
          *first_comma_pp = *pp;
        }
        (*pp)++;
      }
      else
      {
        break;
      }
    }
  }
  //  printf("Ola3: loclev: %i s: %s\n",loclev,*pp);
  while(loclev)
  {
    if((**pp==']') || (((**pp==',') || (**pp=='[')) && (loclev==1)))
    {
      loclev--;
      if(**pp!='[')
        (*pp)++;
    }
    else if(**pp==',')
    {
      // Will this lead to diffrent lengths?
      (*pp)++;
      break;
    }
    else
    {
      printf("Oops: %s\n",*pp);
      exit(-1);
    }
  }
  vector[idx] = -1;
  //  printf("Ola4: returning vector with %i elements and string s: %s\n",idx,*pp);

  return vector;
}

int main(int argc, char* argv[])
{
  int sum = 0;

  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=2)
  {
    char* dl_p = data[i];
    char* dr_p = data[i+1];
    int level = 0;
    int stop = 0;
    char* fcr;
    char* fcl;
    int levelr;
    int levell;
    int* vectorl;
    int* vectorr;

    printf("== Pair %i ==\n",(i/2)+1);
    while(!stop)
    {
      for(int j=0;j<level;j++)
      {
        printf(" ");
      }
      printf("- Compare %s vs %s\n",dl_p,dr_p);

      if((!*dl_p) && (!*dr_p))
      {
        // Match
        break;
      }
      
      //int* parse(char** pp,int* level_p,char** first_comma_pp)
      vectorl = parse(&dl_p,&levell,&fcl);
      vectorr = parse(&dr_p,&levelr,&fcr);

      if((vectorl[0] == -1) && (vectorr[0] == -1))
      {
        //        printf("Ola level %i %i\n",levell,levelr);
        if(levell<levelr)
        {
          break;
        }
        else if(levell>levelr)
        {
          stop = 1;
          break;
        }
      }
      else
      {
        // At least one side has values
        int idx = 0;

        if(abs(levelr-levell)>1)
        {
          if(levell<levelr)
          {
            stop = 1;
          }
          break;
        }
        else if(levell>levelr)
        {
          // take one int from levelr and make a list of it
          if(vectorr[0]==-1)
          {
            //empty, short right means no match
            stop = 1;
            continue;
          }
          else
          {
            if(!fcr && (vectorr[1]!=-1))
            {
              printf("Oops: no comma in vector promote right\n");
              exit(-1);
            }
            vectorr[1]=-1;
            if(fcr)
              dr_p = fcr;
          }
        }
        else if(levell<levelr)
        {
          // take one int from levell and make a list of it
          if(vectorl[0]==-1)
          {
            //empty, short left means match
            continue;
          }
          else
          {
            if(!fcl && (vectorl[1]!=-1))
            {
              printf("Oops: no comma in vector promote left\n");
              exit(-1);
            }
            vectorl[1]=-1;
            if(fcl)
              dl_p = fcl;
          }
        }
        // compare!
        while(1)
        {
          printf("Comparing: %i %i\n",vectorl[idx], vectorr[idx]);
          if(vectorr[idx]==-1 && vectorl[idx]==-1)
          {
            // same length continue comparing!
            break;
          }
          else if(vectorl[idx]==-1)
          {
            // left shorter
            break;
          }
          else if(vectorr[idx]==-1)
          {
            // right shorter
            stop = 1;
            break;
          }
          else if(vectorl[idx] > vectorr[idx])
          {
            stop = 1;
            break;
          }
          else if(vectorl[idx] < vectorr[idx])
          {
            break;
          }
          idx++;
        }
      }
    }
    if(!stop)
    {
      printf("Match: %i\n",(i/2)+1);
      sum += ((i/2)+1);
    }
  }
  printf("Sum: %i\n",sum);
  return 0;
}
