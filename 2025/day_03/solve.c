#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

int highpos(char* buf, int lookfrom, int nomatch)
{
  int len = strlen(buf);

  for(int j=lookfrom;j>=0;j--)
  {
    for(int p=0;p<len;p++)
    {
      if(((buf[p]-'0')==j) && (p!=nomatch))
      {
        return p;
      }
    }
  }
  return -1;
}

int main(int argc, char* argv[])
{
  int sum = 0;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    int len = strlen(data[i]);
    int p1 = highpos(data[i],9,len-1);
    int p2;
    
    p2 = highpos(&(data[i][p1+1]),9,-1) + (p1+1);

    printf("Val: %i (%i %i)\n",(data[i][p1]-'0')*10+(data[i][p2]-'0'),p1,p2);
    sum += (data[i][p1]-'0')*10+(data[i][p2]-'0');
  }
  printf("Sum: %i\n",sum);
  return 0;
}
