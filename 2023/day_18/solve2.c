#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
  char d;
  int len;
  char* color;
} dig_t;

dig_t data[] = {
#include "data.txt"
};

char fmt(char c)
{
  switch(c)
  {
    case '0':
      return 'R';
    case '1':
      return 'D';
    case '2':
      return 'L';
    case '3':
      return 'U';
    default:
      printf("oops\n");
      exit(-1);
  }
}

int hexctoint(char c)
{
  const char* hex = "0123456789abcdef";
  const char* search = hex;
  
  while(*search && *search!=c)
  {
    search++;
  }
  if(!*search)
  {
    printf("oops\n");
    exit(-1);
  }
  return search-hex;
}

int main(int argc, char* argv[])
{
  long y=0;
  long x=0;
  long ys[1024];
  long xs[1024];
  int idx = 0;
  long sum = 0;
  long border = 0;
  long inner = 0;
  
  /* ys[idx] = y; */
  /* xs[idx++] = x; */
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    int nbr = 0;
    char d = fmt(data[i].color[6]);
    
    for(int j=1;j<6;j++)
    {
      nbr = nbr<<4;
      nbr+=hexctoint(data[i].color[j]);
    }
    printf("%s = %c %i\n",data[i].color,d,nbr);
    border += nbr;
    switch(d)
    {
      case 'U':
        y-=nbr;
        break;
      case 'R':
        x+=nbr;
        break;
      case 'D':
        y+=nbr;
        break;
      case 'L':
        x-=nbr;
        break;
    }
    ys[idx] = y;
    xs[idx++] = x;
  }

  printf("Added %i coords\n",idx);

  // Shoelace formula for polygonal area
/* abs( (sum(x[0]*y[1] + ... x[n-1]*y[n]) + x[N]*y[0]) - */
/*      (sum(x[1]*y[0] + ... x[n]*y[n-1]) + x[0]*y[N]) */
/*    ) / 2 */

  for(int i=0;i<idx;i++)
  {
    printf("Point %li:%li\n",ys[i],xs[i]);
    
    sum += xs[i]*ys[i+1] - xs[i+1]*ys[i];
  }
  sum = labs(sum)/2;
  
  printf("Area: %li\n",sum);

  // A = i + b/2 -1 (Picks)
  
  inner = sum - (border/2) + 1;
  printf("Solution: %li\n",inner+border);
  
  return 0;
}
