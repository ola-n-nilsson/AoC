#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};
char mapi[1000][1000];
char map[1000][1000];
int maxy;
int maxx;
int mmy;
int mmx;
int disty[500];
int distx[500];

int cntgal(void)
{
  int galcnt = 0;
  for(int y=0;y<mmy;y++)
  {
    for(int x=0;x<mmx;x++)
    {
      if(map[y][x]=='#')
      {
        galcnt++;
      }
    }
  }
  return galcnt;
}

void populateyx(void)
{
  int oi = 0;
  for(int y=0;y<mmy;y++)
  {
    for(int x=0;x<mmx;x++)
    {
      if(map[y][x]=='#')
      {
        disty[oi]=y;
        distx[oi]=x;
        oi++;
      }
    }
  }
}


void printmap(void)
{
  for(int y=0;y<mmy;y++)
  {
    for(int x=0;x<mmx;x++)
    {
      printf("%c",map[y][x]);
    }
    printf("\n");
  }
}

int main(int argc, char* argv[])
{
  int oy;
  int ox;
  
  maxy = sizeof(data)/sizeof(data[0]);
  maxx = strlen(data[0]);
  memset(mapi,'.',sizeof(mapi));
  memset(map,'.',sizeof(map));
  memset(disty,-1,sizeof(disty));
  memset(distx,-1,sizeof(distx));

  // Yes, I fought about doing it coordinate based, but didn't want to have to think about offsets. Well, that came back to bite me...
  // Rows
  oy=0;
  for(int y=0;y<maxy;y++)
  {
    int galaxies = 0;
    
    for(int x=0;x<maxx;x++)
    {
      if(data[y][x]!='.')
      {
        galaxies++;
        break;
      }
    }
    if(!galaxies)
    {
      oy+=2; //No need to write empty row...
    }
    else
    {
      for(int x=0;x<maxx;x++)
      {
        mapi[oy][x] = data[y][x];
      }
      oy++;
    }
  }
  mmy = oy;
  
  // Colums
  ox = 0;
  for(int x=0;x<maxx;x++)
  {
    int galaxies = 0;
    
    for(int y=0;y<mmy;y++)
    {
      if(mapi[y][x]!='.')
      {
        galaxies++;
        break;
      }
    }
    if(!galaxies)
    {
      ox+=2; //No need to write empty row...
    }
    else
    {
      for(int y=0;y<mmy;y++)
      {
        map[y][ox] = mapi[y][x];
      }
      ox++;
    }
  }
  mmx = ox;

  printmap();
  printf("Max: %i:%i\n",mmy,mmx);
  {
    int galcnt = cntgal();
    long sum = 0;
    
    printf("Cnt of galaxies: %i\n",galcnt);
    populateyx();

    for(int i=0;i<galcnt;i++)
    {
      for(int j=i+1;j<galcnt;j++)
      {
        int dist = abs(disty[i]-disty[j])+abs(distx[i]-distx[j]);
        
        printf("Distance between %i (%i:%i) and %i (%i:%i)\n",i,disty[i],distx[i],j,disty[j],distx[j]);
        printf("is %i\n",dist);
        sum+=dist;
        // 5 6:1
        // 9 11:5
        // distance 9 = abs(6-11)+abs(1-5) = 9
      }
    }
    printf("Distance sum: %li\n",sum);
  }
  return 0;
}
