#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>

char data[102400];

int readnum(char* p, unsigned long* num)
{
  int digits = 0;

  *num = 0;
  while(*p>='0' && *p<='9')
  {
    *num *= 10;
    *num += *p - '0';
    p++;
    digits++;
  }
  return digits;
}

int main(int argc, char* argv[])
{
  char* p=data;
  unsigned long sum = 0;
  unsigned long num1,num2;
  int step = 0;
  int fd;
  size_t rd = 0;
  int enabled = 1;
  
  memset(data,0,sizeof(data));
  fd = open("data.txt",O_RDONLY);
  rd = read(fd,data,sizeof(data));
  printf("Read: %lu\n",(long unsigned)rd);
  
  // mul(123,456)
  while(*p)
  {
    if(*p=='d' && *(p+1)=='o')
    {
      // "do()"
      if(*(p+2)=='(' && *(p+3)==')')
      {
        enabled = 1;
      }
      // "don't()"
      else if (*(p+2)=='n' &&
               *(p+3)=='\'' &&
               *(p+4)=='t' &&
               *(p+5)=='(' &&
               *(p+6)==')')
      {
        enabled = 0;
      }
      p++;
      continue;
    }
    switch(step)
    {
      case 0:
        if(*p=='m')
        {
          step = 1;
        }
        p++;
        break;
      case 1:
        if(*p=='u')
        {
          step = 2;
        }
        else
        {
          step = 0;
        }
        p++;
        break;
      case 2:
        if(*p=='l')
        {
          step = 3;
        }
        else
        {
          step = 0;
        }
        p++;
        break;
      case 3:
        if(*p=='(')
        {
          step = 4;
        }
        else
        {
          step = 0;
        }
        p++;
        break;
      case 4:
        {
          int digits;

          num1 = 0;
          digits = readnum(p, &num1);
          p+=digits;
          if((digits>0) && (digits<4))
          {
            step = 5;
          }
          else
          {
            step = 0;
          }
          break;
        }
      case 5:
        if(*p==',')
        {
          step = 6;
        }
        else
        {
          step = 0;
        }
        p++;
        break;
      case 6:
        {
          int digits;

          num2 = 0;
          digits = readnum(p, &num2);
          p+=digits;
          if((digits>0) && (digits<4))
          {
            step = 7;
          }
          else
          {
            step = 0;
          }
          break;
        }
      case 7:
        if(*p==')')
        {
          step = 8;
        }
        else
        {
          step = 0;
        }
        p++;
        break;
    }
    if(step==8)
    {
      step = 0;
      if(enabled)
      {
        printf("Mul %lu * %lu\n",num1,num2);
        sum += num1*num2;
      }
    }
  }
  printf("Sum %lu\n",sum);
  printf("Len: %lu\n",(unsigned long)(p-data));
  return 0;
}
