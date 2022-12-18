#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
  int x;
  int y;
  int z;
} cubepos_t;

cubepos_t data[] = {
#include "data.txt"
};

char space[20][20][20];

int main(int argc, char* argv[])
{
  int min_x = INT_MAX;
  int max_x = INT_MIN;
  int min_y = INT_MAX;
  int max_y = INT_MIN;
  int min_z = INT_MAX;
  int max_z = INT_MIN;

  memset(space,0,sizeof(space));
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    if(data[i].x<min_x)
    {
      min_x = data[i].x;
    }
    if(data[i].x>max_x)
    {
      max_x = data[i].x;
    }
    if(data[i].y<min_y)
    {
      min_y = data[i].y;
    }
    if(data[i].y>max_y)
    {
      max_y = data[i].y;
    }
    if(data[i].z<min_z)
    {
      min_z = data[i].z;
    }
    if(data[i].z>max_z)
    {
      max_z = data[i].z;
    }

    space[data[i].x][data[i].y][data[i].z] = '#';
  }

  int exposed = 0;
  
  for(int z=0;z<20;z++)
    for(int y=0;y<20;y++)
      for(int x=0;x<20;x++)
      {
        if(space[x][y][z])
        {
          // x-1
          if(x != 0)
          {
            if(!space[x-1][y][z])
            {
              exposed++;
            }
          }
          else
          {
            exposed++;
          }
          //x+1
          if(x != 19)
          {
            if(!space[x+1][y][z])
            {
              exposed++;
            }
          }
          else
          {
            exposed++;
          }
          // y-1
          if(y != 0)
          {
            if(!space[x][y-1][z])
            {
              exposed++;
            }
          }
          else
          {
            exposed++;
          }
          //y+1
          if(y != 19)
          {
            if(!space[x][y+1][z])
            {
              exposed++;
            }
          }
          else
          {
            exposed++;
          }
          // z-1
          if(z != 0)
          {
            if(!space[x][y][z-1])
            {
              exposed++;
            }
          }
          else
          {
            exposed++;
          }
          //z+1
          if(z != 19)
          {
            if(!space[x][y][z+1])
            {
              exposed++;
            }
          }
          else
          {
            exposed++;
          }
        }
      }
  
  printf("Min: %i:%i:%i\n",min_x,min_y,min_z);
  printf("Max: %i:%i:%i\n",max_x,max_y,max_z);

  printf("Exposed: %i\n",exposed);
  return 0;
}
