#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};
long disty[500];
long distx[500];
int maxy;
int maxx;
int galcnt = 0;
int emptyrows[200];
int emptycols[200];
int eri = 0;
int eci = 0;
int factor = 1000000;

void populateyx(void)
{
  for(int y=0;y<maxy;y++)
  {
    int xcnt = 0;
    
    for(int x=0;x<maxx;x++)
    {
      if(data[y][x]=='#')
      {
        disty[galcnt]=y;
        distx[galcnt]=x;
        xcnt++;
        galcnt++;
      }
    }
    if(!xcnt)
    {
      emptyrows[eri++]=y;
    }
  }

  for(int x=0;x<maxx;x++)
  {
    int ycnt=0;
    for(int y=0;y<maxy;y++)
    {
      if(data[y][x]=='#')
      {
        ycnt++;
      }
    }
    if(!ycnt)
    {
      emptycols[eci++]=x;
    }
  }
  
}


int main(int argc, char* argv[])
{
  
  maxy = sizeof(data)/sizeof(data[0]);
  maxx = strlen(data[0]);
  memset(disty,-1,sizeof(disty));
  memset(distx,-1,sizeof(distx));
  memset(emptyrows,-1,sizeof(emptyrows));
  memset(emptycols,-1,sizeof(emptycols));
  
  populateyx();

  // offset y
  for(int i=0;i<eri;i++)
  {
    for(int j=0;j<galcnt;j++)
    {
      if(disty[j]>(emptyrows[i]+(i*(factor-1))))
      {
        disty[j]+=factor-1;
      }
    }
  }
  // offset x
  for(int i=0;i<eci;i++)
  {
    for(int j=0;j<galcnt;j++)
    {
      if(distx[j]>(emptycols[i]+(i*(factor-1))))
      {
        distx[j]+=factor-1;
      }
    }
  }

  {
    unsigned long sum = 0;
    unsigned long faksum = 0;
    unsigned long sumrest = 0;
    
    printf("Cnt of galaxies: %i\n",galcnt);

    for(int i=0;i<galcnt;i++)
    {
      for(int j=i+1;j<galcnt;j++)
      {
        unsigned long dist = ((unsigned long)abs(disty[i]-disty[j]))+abs(distx[i]-distx[j]);
        
        printf("Distance between %i (%li:%li) and %i (%li:%li)\n",i,disty[i],distx[i],j,disty[j],distx[j]);
        printf("is %lu\n",dist);
        sum+=dist;
        sumrest += dist%factor;
        faksum += dist/factor;
        
        // 5 6:1
        // 9 11:5
        // distance 9 = abs(6-11)+abs(1-5) = 9
      }
    }
    printf("Distance sum: %lu (%lu %lu)\n",sum,faksum,sumrest);
  }

  
  
  //
  return 0;
}

