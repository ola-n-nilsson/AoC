#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#if 1
#define NBR_CONNECT (1000)
const int data[] = {
#include "data.txt"
};
#else
#define NBR_CONNECT (10)
const int data[] = {
#include "data2.txt"
};
#endif

typedef struct sdist_t {
  int p1;
  int p2;
  unsigned long dist;
}sdist_t;

int sdistp = 0;
sdist_t sdist[2000000];

unsigned long dist(int z1,int y1,int x1,int z2,int y2,int x2)
{
  unsigned long z = (long)(z1-z2)*(long)(z1-z2);
  unsigned long y = (long)(y1-y2)*(long)(y1-y2);
  unsigned long x = (long)(x1-x2)*(long)(x1-x2);

  return (z+y+x);
}

unsigned long map[1024][1024];


char con[1024][1024];

int visited[1024];

int connected(int idx)
{
  int ret = 1;
  visited[idx]=1;

  for(int i=0;i<((sizeof(data)/sizeof(data[0]))/3);i++)
  {
    if(con[idx][i] && !visited[i])
    {
      ret += connected(i);
    }
  }
  return ret;
}

int compint(const void* e1, const void* e2)
{
  int* d1 = (int*)e1;
  int* d2 = (int*)e2;

  return *d1<*d2;
}

int comp(const void* e1, const void* e2)
{
  sdist_t* d1 = (sdist_t*)e1;
  sdist_t* d2 = (sdist_t*)e2;

  return d1->dist>d2->dist;
}

int main(int argc, char* argv[])
{

  memset(map,-1,sizeof(map));
  memset(con,0,sizeof(con));
  memset(visited,0,sizeof(visited));
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=3)
  {
    for(int j=0;j<(sizeof(data)/sizeof(data[0]));j+=3)
    {
      int m1 = i/3;
      int m2 = j/3;
      
      if((map[m1][m2]==(unsigned long)-1) && (i!=j))
      {
        
        map[m1][m2] = dist(data[i],data[i+1],data[i+2],data[j],data[j+1],data[j+2]);
        map[m2][m1] = map[m1][m2];
        sdist[sdistp].p1 = i;
        sdist[sdistp].p2 = j;
        sdist[sdistp].dist = map[m1][m2];
        sdistp++;
      }
    }
  }

  qsort (sdist, sdistp, sizeof(sdist_t), comp);

  {
    int i=0;
    int size;
    
    for(int i=0;i<NBR_CONNECT;i++)
    {
      con[sdist[i].p1/3][sdist[i].p2/3] = 1;
      con[sdist[i].p2/3][sdist[i].p1/3] = 1;
    }
    do
    {
      con[sdist[i].p1/3][sdist[i].p2/3] = 1;
      con[sdist[i].p2/3][sdist[i].p1/3] = 1;
      memset(visited,0,sizeof(visited));
      size = connected(0);
      i++;
      if(i>6000)
      {
        printf("Oops %i\n",size);
        exit(-1);
      }
    } while(size<1000);
    printf("Added %i\n",i);
    printf("Result %li\n",(long)data[sdist[i-1].p1]*data[sdist[i-1].p2]);
  }

  return 0;
}
