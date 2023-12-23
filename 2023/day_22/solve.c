#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
  int x1;
  int y1;
  int z1;
  int x2;
  int y2;
  int z2;
  int origi;
} brick_t;

brick_t data[] = {
#include "data.txt"
};

int cmpfunc (const void * a, const void * b)
{
  brick_t* ab = (brick_t*)a;
  brick_t* bb = (brick_t*)b;
  
   return ( ab->z1 - bb->z1 );
}

int nbrofbricks;

#define MAXH (1000)
int room[MAXH][10][10];

int bsupport[2000][10];
int bsidx[2000];
int bsupportedby[2000][10];
int bsbyidx[2000];

// Brick supports supbrick
void insert(int brick,int supbrick)
{
  for(int i=0;i<bsidx[brick];i++)
  {
    if(bsupport[brick][i] == supbrick)
    {
      return;
    }
  }
  bsupport[brick][bsidx[brick]] = supbrick;
  (bsidx[brick])++;
}

// brick is supported by supbrick
void insertby(int brick,int supbrick)
{
  for(int i=0;i<bsbyidx[brick];i++)
  {
    if(bsupportedby[brick][i] == supbrick)
    {
      return;
    }
  }
  bsupportedby[brick][bsbyidx[brick]] = supbrick;
  (bsbyidx[brick])++;
}


int main(int argc, char* argv[])
{
  int maxy;
  int maxx;
  int maxz;
  
  nbrofbricks = (sizeof(data)/sizeof(data[0]));

  for(int i=0;i<nbrofbricks;i++)
  {
    data[i].origi = i;
    if(data[i].z1>maxz)
    {
      maxz = data[i].z1;
    }
    if(data[i].z2>maxz)
    {
      maxz = data[i].z2;
    }
    if(data[i].x1>maxx)
    {
      maxx = data[i].x1;
    }
    if(data[i].x2>maxx)
    {
      maxx = data[i].x2;
    }
    if(data[i].x1<0 || data[i].x2<0)
    {
      printf("Oops!\n");
      exit(-1);
    }
    if(data[i].y1>maxy)
    {
      maxy = data[i].y1;
    }
    if(data[i].y2>maxy)
    {
      maxy = data[i].y2;
    }
    if(data[i].y1<0 || data[i].y2<0)
    {
      printf("Oops!\n");
      exit(-1);
    }
    if((data[i].y1 - data[i].y2) && (data[i].x1 - data[i].x2))
    {
      printf("Brick %i is diagonal in xy\n",i);
      exit(-1);
    }
    if((data[i].z1 - data[i].z2))
    {
      int ydiff = abs(data[i].y1 - data[i].y2);
      int xdiff = abs(data[i].x1 - data[i].x2);
      int xydiff = ydiff+xdiff;

      if(xydiff)
      {
        printf("Brick %i has slope both in xy and z\n",i);
        exit(-1);
      }
      if(xydiff && (abs(data[i].z1 - data[i].z2) != xydiff))
      {
        printf("Brick %i has different slope in xy to z\n",i);
      }
    }
    if(data[i].x1 > data[i].x2)
    {
      printf("Brick %i x1 > x2\n",i);
      exit(-1);
    }
    if(data[i].y1 > data[i].y2)
    {
      printf("Brick %i y1 > y2\n",i);
      exit(-1);
    }
    if(data[i].z1 > data[i].z2)
    {
      printf("Brick %i z1 > z2\n",i);
      exit(-1);
    }
  }
  printf("Max: %i:%i\n",maxy,maxx);
  printf("Max heigth: %i\n",maxz);
  // For my data 9:9 is ok in xy
  // There is no diagonal in xy.
  // If z differs xy doesn't
  // For all x,y,z n1 is smaller or equal to n2

  {
    int rounds = 0;
    int moved = 1;

    // Prepair room
    memset(room,-1,sizeof(room));
    for(int i=0;i<nbrofbricks;i++)
    {
      int deltay = 0;
      int deltax = 0;
      int deltaz = 0;
      int len = 0;
      int z = data[i].z1;
      int y = data[i].y1;
      int x = data[i].x1;
      
      if(data[i].x1 - data[i].x2)
      {
        deltax= 1;
        len = data[i].x2 - data[i].x1;
      }
      else if(data[i].y2 - data[i].y1)
      {
        deltay= 1;
        len = data[i].y2 - data[i].y1;
      }
      else if (data[i].z2 - data[i].z1)
      {
        deltaz= 1;
        len = data[i].z2 - data[i].z1;
      }
      for(int d=0;d<=len;d++)
      {
        room[z+(d*deltaz)][y+(d*deltay)][x+(d*deltax)] = i;
      }
    }

    qsort(data,nbrofbricks,sizeof(brick_t),cmpfunc);

    // Move
    while(moved)
    {
      moved = 0;
      rounds++;
      
      for(int i=0;i<nbrofbricks;i++)
      {
        int deltay = 0;
        int deltax = 0;
        int len = 0;
        int support = 0;
        int z;
        int y = data[i].y1;
        int x = data[i].x1;
        
        if(data[i].x1 - data[i].x2)
        {
          deltax= 1;
          len = data[i].x2 - data[i].x1;
        }
        else if(data[i].y2 - data[i].y1)
        {
          deltay= 1;
          len = data[i].y2 - data[i].y1;
        }

        //Check
        {
          for(z=data[i].z1;(z>1) && !support;z--)
          {
            //Resting place?
            for(int d=0;d<=len;d++)
            {
              if(room[z-1][y+(d*deltay)][x+(d*deltax)] != -1)
              {
                printf("Support at: %i\n",z-1);
                support = 1;
                break;
              }
            }
          }
          if(support)
          {
            z++;
            printf("Brick %i rest at %i (supported)\n",i,z);
          }
          else
          {
            printf("Brick %i rest at %i\n",i,z);
          }
          if(z != data[i].z1)
          {
            if(deltay || deltax) 
            {
              for(int d=0;d<=len;d++)
              {
                printf("Put brick %i at %i:%i:%i\n",i,z,y+(d*deltay),x+(d*deltax));
                room[z][y+(d*deltay)][x+(d*deltax)] = i;
                room[data[i].z1][y+(d*deltay)][x+(d*deltax)] = -1;
              }
            }
            else
            {
              int d;
              len = data[i].z2 - data[i].z1;
              for(d=0;d<=len;d++)
              {
                // Clear all of it.
                room[data[i].z1+d][y][x] = -1;
              }
              for(d=0;d<=len;d++)
              {
                printf("Put brick %i at %i:%i:%i\n",i,z+d,y,x);
                room[z+d][y][x] = i;
              }
            }
            data[i].z2 = data[i].z2 - (data[i].z1 - z);
            data[i].z1 = z;
            moved = 1;
          }
        }
      }
    }
    printf("Stopped moving after %i rounds\n",rounds);
  }

  
  memset(bsupport,0,sizeof(bsupport));
  memset(bsidx,0,sizeof(bsidx));
  memset(bsupportedby,0,sizeof(bsupportedby));
  memset(bsbyidx,0,sizeof(bsbyidx));
  
  // At rest, who supports who?
  {
    for(int i=0;i<nbrofbricks;i++)
    {
      int deltay = 0;
      int deltax = 0;
      int len = 0;
      int z = data[i].z1;
      int y = data[i].y1;
      int x = data[i].x1;
        
      if(data[i].x1 - data[i].x2)
      {
        deltax= 1;
        len = data[i].x2 - data[i].x1;
      }
      else if(data[i].y2 - data[i].y1)
      {
        deltay= 1;
        len = data[i].y2 - data[i].y1;
      }

      if(deltax || deltay)
      {
        for(int d=0;d<=len;d++)
        {
          if(room[z-1][y+(d*deltay)][x+(d*deltax)] != -1)
          {
            // Brick is supported by supbrick
            insertby(i,room[z-1][y+(d*deltay)][x+(d*deltax)]);
          }
          if(room[z+1][y+(d*deltay)][x+(d*deltax)] != -1)
          {
            // Brick is supported by supbrick
            insert(i,room[z+1][y+(d*deltay)][x+(d*deltax)]);
          }
        }
      }
      else
      {
        // Support in z
        if(room[z-1][y][x]!=-1)
        {
          // Brick is supported by supbrick
          insertby(i,room[z-1][y][x]);
        }
        if(room[data[i].z2+1][y][x]!=-1)
        {
          // Brick supports supbrick
          insert(i,room[data[i].z2+1][y][x]);
        }
      }
    }
  }


  // Print bricks and who they support
  {
    for(int i=0;i<nbrofbricks;i++)
    {
      /* printf("Brick %i supports:",i); */
      /* for(int j=0;j<bsidx[i];j++) */
      /* { */
      /*   printf("%i ",bsupport[i][j]); */
      /* } */
      /* printf("\n"); */
      printf("%i resting on {",i);
      for(int j=0;j<bsbyidx[i];j++)
      {
        printf("%i, ",bsupportedby[i][j]);
      }
      printf("}\n");
             
    }
  }

  // Analyse loose bricks
  {
    int loose = 0;
    
    for(int i=0;i<nbrofbricks;i++)
    {
      if(!bsidx[i])
      {
        loose++;
        continue;
      }
      // All we support must have more supports than us
      int willfall = 0;
      
      for(int j=0;j<bsidx[i];j++)
      {
        if(bsbyidx[bsupport[i][j]]>1)
        {
          continue;
        }
        willfall = 1;
        break;
      }
      if(!willfall)
      {
        loose++;
      }
    }
    printf("Loose: %i\n",loose);
  }

  return 0;
}


