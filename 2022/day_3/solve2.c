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
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=3)
  {
    const char* str1 = data[i];
    const char* str2 = data[i+1];
    const char* str3 = data[i+2];
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len3 = strlen(str3);
    char match = 0;

    for(int i=0;i<len1;i++)
    {
      for(int j=0;j<len2;j++)
      {
        if(str1[i]==str2[j])
        {
          for(int k=0;k<len3;k++)
          {
            if(str1[i]==str3[k])
            {
              match = str3[k];
            }
          }
        }
      }
    }
    printf("Str1: %s\n",str1);
    printf("Str2: %s\n",str1);
    printf("Str3: %s\n",str1);
    printf("Match: %c\n\n",match);

    if(match >= 'a' && match<='z')
    {
      prio += match - 'a' + 1;
    }
    else if(match >= 'A' && match<='Z')
    {
      prio += match - 'A' + 27;
    }
    else
    {
      printf("Oops\n");
    }

  }
  
  printf("Prio: %i\n",prio);
  return 0;
}
