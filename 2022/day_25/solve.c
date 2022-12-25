#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

// 2, 1, 0, minus (written -), and double-minus (written =)

char* data[] = {
#include "data.txt"
};

long long snafu2num(char* in_p)
{
  int len = strlen(in_p);
  long long exp = 1;
  long long num = 0;
  
  for(int idx=len-1;idx>=0;idx--)
  {
    int val;
    
    switch(in_p[idx])
    {
      case '2':
        val = 2;
        break;
      case '1':
        val = 1;
        break;
      case '0':
        val = 0;
        break;
      case '-':
        val = -1;
        break;
      case '=':
        val = -2;
        break;
      default:
        printf("Oops\n");
        exit(-1);
        
    }
    num += exp* val;
    exp *=5;
  }
  return num;
}

void num2snafu_helper(long long num)
{
  // 2 pow	2 pow -1 lower	2 pow - 2 lower	pow	pow -1 lower	pow - 2 lower
  long long tab[22][6];
  long long exp = 1;
  int reminder = 0;
  int y;
  int x;
  
  memset(tab,0,sizeof(tab));
  for(y=0;y<22;y++)
  {
    tab[y][0] = exp * 2;
    tab[y][3] = exp;
    exp *= 5;
  }
  for(y=1;y<22;y++)
  {
    tab[y][1] = tab[y][0] - tab[y-1][3];  // 2pow - 1 lower
    tab[y][2] = tab[y][0] - tab[y-1][0];  // 2pow - 2 lower
    tab[y][4] = tab[y][3] - tab[y-1][3];  // pow - 1 lower
    tab[y][5] = tab[y][3] - tab[y-1][0];  // pow - 2 lower
  }

  for(y=21;y>0;y--)
  {
    for(x=0;x<6;x++)
    {
      if(tab[y][x]<num)
      {
        const int vals[] = { 2, 2, 2, 1, 1, 1};
        const int reminders[] = {0,-1,-2,0,-1,-2};
        const char chars[] = "=-012xxxx";
        
        int val = vals[x] + reminder;
        printf("%i: char %c",y, chars[2+val]);
        num -= tab[y][x];
        reminder = reminders[x];
        break;
      }
    }
    if(x==6)
    {
      const char chars[] = "=-012xxxx";
      printf("%i: char %c",y,chars[2+reminder]);
      reminder = 0;
    }
    printf("\n");
  }
  printf("%i Num left: %lli reminder: %i\n",y,num,reminder);
}

int main(int argc, char* argv[])
{
  long long sum = 0;
  long long val;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    val = snafu2num(data[i]);
    printf("Value: %lli\n",val);
    sum += val;
  }
  printf("Sum: %lli\n",sum);
  num2snafu_helper(sum);
  printf("Part1: 20=2-02-0---02=22=21 == %lli\n",snafu2num("20=2-02-0---02=22=21"));

  return 0;
}
