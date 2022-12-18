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
  int cnt = 0;
  
  memset(space,0,sizeof(space));
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    cnt++;
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
          printf("Check for %i:%i:%i\n",x,y,z);

          // x-1
          if(x != 0)
          {
            int x2;
            printf("Check x-1 for %i:%i:%i\n",x,y,z);
            for(x2 = x-1;x2>-1;x2--)
            {
              if(space[x2][y][z])
              {
                break;
              }
            }
            printf("x2 i -1 %i\n",x2);
            if(x2==-1)
            {
              printf("Exposed x-1\n");
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
            int x2;
            for(x2 = x+1;x2<20;x2++)
            {
              if(space[x2][y][z])
              {
                break;
              }
            }
            printf("x2 i +1 %i\n",x2);
            if(x2==20)
            {
              printf("Exposed x+1\n");
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
            int y2;
            for(y2 = y-1;y2>-1;y2--)
            {
              if(space[x][y2][z])
              {
                break;
              }
            }
            printf("y2 i -1 %i\n",y2);
            if(y2==-1)
            {
              printf("Exposed y-1\n");
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
            int y2;
            for(y2 = y+1;y2<20;y2++)
            {
              if(space[x][y2][z])
              {
                break;
              }
            }
            printf("y2 i +1 %i\n",y2);
            if(y2==20)
            {
              printf("Exposed y+1\n");
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
            int z2;
            for(z2 = z-1;z2>-1;z2--)
            {
              if(space[x][y][z2])
              {
                break;
              }
            }
            printf("z2 i -1 %i\n",z2);
            if(z2==-1)
            {
              printf("Exposed z-1\n");
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
            int z2;
            for(z2 = z+1;z2<20;z2++)
            {
              if(space[x][y][z2])
              {
                break;
              }
            }
            printf("z2 i +1 %i\n",z2);
            if(z2==20)
            {
              printf("Exposed z+1\n");
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
  printf("Cubes: %i sides: %i\n",cnt,cnt*6);

  printf("Exposed: %i\n",exposed);
  return 0;
}
