#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

const char* data[] = {
  #include "data.txt"
};


/* Lowercase item types a through z have priorities 1 through 26. */
/* Uppercase item types A through Z have priorities 27 through 52. */


int main(int argc, char* argv[])
{
  int prio = 0;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    const char* str = data[i];
    int len = strlen(str);
    int adding = 0;
    
    printf("Str: %s ",str);
    //    printf("D: %s\n",data[i]);
    for(int j=0;j<len/2;j++)
    {
      for(int c=len/2; c<len;c++)
      {
        if(str[j] == str[c])
        {
          printf("matched: %c ", str[c]);
          if(str[c] >= 'a' && str[c]<='z')
          {
            adding = str[c] - 'a' + 1;
          }
          else if(str[c] >= 'A' && str[c]<='Z')
          {
            adding = str[c] - 'A' + 27;
          }
          else
          {
            printf("Oops\n");
          }
        }
      }
    }
    prio += adding;
    printf("Adding: %i\n",adding);
  }
  printf("Prio: %i\n",prio);
  return 0;
}
