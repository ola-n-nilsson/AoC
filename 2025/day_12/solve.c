#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

// Well, fun to share this with you. I was about to give up, but decided to at least count if
// the #s of all the shapes could fit the area. Once I had the number of areas that could fit,
// why not input it? And... I'm still not sure if an area could be generated that fulfills my
// assumption but can't fit the pieces.

#if 0
char* shapes[] = {
#include "data2s.txt"
};
int areas[] = {
#include "data2r.txt"
};
#else
char* shapes[] = {
#include "datas.txt"
};
int areas[] = {
#include "datar.txt"
};
#endif

int cnt(char* s)
{
  int ret = 0;

  for(int i=0;i<3;i++)
  {
    if(s[i]=='#')
    {
      ret++;
    }
  }
  return ret;
}

int main(int argc, char* argv[])
{
  int density[6];
  int could = 0;
  
  memset(density,0,sizeof(density));
         
  for(int i=0;i<6;i++)
  {
    density[i] = cnt(shapes[i*4]) +
      cnt(shapes[(i*4)+1]) +
      cnt(shapes[(i*4)+2]);
    printf("Shape: %i density: %i\n",i,density[i]);
  }

  for(int i=0;i<(sizeof(areas)/sizeof(areas[0]));i+=8)
  {
    int weight = 0;
    int room = (areas[i])*(areas[i+1]);

    for(int j=0;j<6;j++)
    {
      weight += areas[i+(2+j)] * density[j];
    }
    printf("For area %i room %i weight %i ",i/8,room,weight);
    if(weight > room)
    {
      printf("will not fit\n");
    }
    else
    {
      printf("COULD fit\n");
      could++;
    }
  }

  printf("Out of %i areas %i could fit\n",(int)(sizeof(areas)/sizeof(areas[0]))/8,could);
  
  return 0;
}
