#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

int fill[200][200];
int fill2[200][200]; // 0 not part of region, 1 edge, 2 internal
int dir[400][400]; //00 Part of north surface, 01, part of east  surface, 10 part of west surface and 11 for south

int area[200*200];
int per[200*200];
int surf[200*200];
int idx = 0;

int maxy;
int maxx;

#if 0
       ################                                                                                                                     
      #................#                                                                                                                    
       #................#                                                                                                                   
      #.................#                                                                                                                   
       ###...#.....##..#                                                                                                                    
       #  #.# #...#  ##                                                                                                                     
       #  #.# #...#                                                                                                                         
          ## #..###                                                                                                                         
          # #..#                                                                                                                            
            #..#                                                                                                                            
        ####....#                                                                                                                           
       #.......#                                                                                                                            
      #.........#                                                                                                                           
      ##.......#  #                                                                                                                         
      # #.......###                                                                                                                         
      ##..........#                                                                                                                         
      ##.#.....###                                                                                                                          
        # #...#                                                                                                                             
           ###                                                                                                                              

.......AAAAAAAAAAAAAAAA.......
......AAAAAAAAAAAAAAAAAA......
.......AAAAAAAAAAAAAAAAAA.....
......AAAAAAAAAAAAAAAAAAA.....
.......AAAAAAAAAAAAAAAAA......
.......A..AAALAAAAA..AA.......
.......A..AAALAAAAA...........
..........AA.AAAAAA...........
..........A.AAAA..............
............AAAA..............
........AAAAAAAAA.............
.......AAAAAAAAA..............
......AAAAAAAAAAA.............
......AAAAAAAAAA..A...........
......A.AAAAAAAAAAA...........
......AAAAAAAAAAAAA...........
......AAAAAAAAAAAA............
........A.AAAAA...............
...........AAA................
..............................

       
345
2.6
107       
#endif

       
void fillrec(char c,int y,int x,int *rarea,int *rper)
{
  fill2[y][x] = 2;
  if(y>0)
  {
    if((data[y-1][x]==c) && (!fill[y-1][x]))
    {
      fill[y-1][x] = 1;
      fillrec(c,y-1,x,rarea,rper);
    }
  }
  if((y+1)<maxy)
  {
    if((data[y+1][x]==c) && (!fill[y+1][x]))
    {
      fill[y+1][x] = 1;
      fillrec(c,y+1,x,rarea,rper);
    }
  }
  if(x>0)
  {
    if((data[y][x-1]==c) && (!fill[y][x-1]))
    {
      fill[y][x-1] = 1;
      fillrec(c,y,x-1,rarea,rper);
    }
  }
  if((x+1)<maxx)
  {
    if((data[y][x+1]==c) && (!fill[y][x+1]))
    {
      fill[y][x+1] = 1;
      fillrec(c,y,x+1,rarea,rper);
    }
  }
  (*rarea)++;
  if((!y) || (data[y-1][x]!=c))
  {
    (*rper)++;
    fill2[y][x] = 1;
  }
  if(((y+1)==maxy) || (data[y+1][x]!=c))
  {
    (*rper)++;
    fill2[y][x] = 1;
  }
  if((!x) || (data[y][x-1]!=c))
  {
    (*rper)++;
    fill2[y][x] = 1;
  }
  if(((x+1)==maxx) || (data[y][x+1]!=c))
  {
    (*rper)++;
    fill2[y][x] = 1;
  }
  
  return;
}

void fillregion(int y,int x)
{
  int rarea = 0;
  int rper = 0;
  int surface = 0;
  
  memset(fill2,0,sizeof(fill2));
  memset(dir,0,sizeof(dir));
  fill[y][x] = 1;
  fillrec(data[y][x],y,x,&rarea,&rper);

  // Find surfaces
  //00 Part of north surface, 01, part of east  surface, 10 part of west surface and 11 for south
  {
    for(int i=0;i<maxy;i++)
    {
      int empty = 1;
      
      for(int j=0;j<maxx;j++)
      {
        // West surfaces 10
        if((fill2[i][j]==1) && empty && !dir[(i*2)+1][j*2])
        {
          surface++;
          dir[(i*2)+1][j*2] = surface;
          for(int k=i-1;k>=0;k--)
          {
            if(fill2[k][j]==1 && ((j==0) || (fill2[k][j-1])==0))
            {
              dir[(k*2)+1][j*2] = surface;
            }
            else
            {
              break;
            }
          }
          for(int k=i+1;k<maxy;k++)
          {
            if(fill2[k][j]==1 && ((j==0) || fill2[k][j-1]==0))
            {
              dir[(k*2)+1][j*2] = surface;
            }
            else
            {
              break;
            }
          }
        }
        empty = !fill2[i][j];
      }
    }

    for(int j=0;j<maxx;j++)
    {
      int empty = 1;
      
      for(int i=0;i<maxy;i++)
      {
        // North surfaces 00
        if((fill2[i][j]==1) && empty && !dir[i*2][j*2])
        {
          surface++;
          dir[i*2][j*2] = surface;
          for(int k=j-1;k>=0;k--)
          {
            if(fill2[i][k]==1 && ((i==0) || fill2[i-1][k]==0))
            {
              dir[i*2][k*2] = surface;
            }
            else
            {
              break;
            }
          }
          for(int k=j+1;k<maxx;k++)
          {
            if(fill2[i][k]==1 && ((i==0) || (fill2[i-1][k]==0)))
            {
              dir[i*2][k*2] = surface;
            }
            else
            {
              break;
            }
          }
        }
        empty = !fill2[i][j];
      }
    }

    for(int i=0;i<maxy;i++)
    {
      int empty = 1;
      
      for(int j=(maxx-1);j>=0;j--)
      {
        // East surfaces 01
        if((fill2[i][j]==1) && empty && !dir[i*2][(j*2)+1])
        {
          surface++;
          dir[i*2][(j*2)+1] = surface;
          for(int k=i-1;k>=0;k--)
          {
            if(fill2[k][j]==1 && (((j+1)==maxx) || fill2[k][j+1]==0))
            {
              dir[(k*2)][(j*2)+1] = surface;
            }
            else
            {
              break;
            }
          }
          for(int k=i+1;k<maxy;k++)
          {
            if(fill2[k][j]==1 && (((j+1)==maxx) || fill2[k][j+1]==0))
            {
              dir[k*2][(j*2)+1] = surface;
            }
            else
            {
              break;
            }
          }
        }
        empty = !fill2[i][j];
      }
    }

    for(int j=0;j<maxx;j++)
    {
      int empty = 1;
      
      for(int i=(maxy-1);i>=0;i--)
      {
        // South surfaces 11
        if((fill2[i][j]==1) && empty && !dir[(i*2)+1][(j*2)+1])
        {
          surface++;
          dir[(i*2)+1][(j*2)+1] = surface;
          for(int k=j-1;k>=0;k--)
          {
            if(fill2[i][k]==1 && (((i+1)==maxy)||(fill2[i+1][k]==0)))
            {
              dir[(i*2)+1][(k*2)+1] = surface;
            }
            else
            {
              break;
            }
          }
          for(int k=j+1;k<maxx;k++)
          {
            if(fill2[i][k]==1 && (((i+1)==maxy)||(fill2[i+1][k]==0)))
            {
              dir[(i*2)+1][(k*2)+1] = surface;
            }
            else
            {
              break;
            }
          }
        }
        empty = !fill2[i][j];
      }
    }
  }

  printf("Region at %i:%i %c a: %i p: %i s:%i\n",y,x,data[y][x],rarea,rper,surface);
  area[idx] = rarea;
  per[idx] = rper;
  surf[idx] = surface;
  idx++;

#if 0
  printf("Region:\n");
  for(int i=0;i<maxy;i++)
  {
    for(int j=0;j<maxx;j++)
    {
      if(fill2[i][j]==1)
      {
        printf("#");
      }
      else if(fill2[i][j]==2)
      {
        printf(".");
      }
      else
      {
        printf(" ");
      }
    }
    printf("\n");
  }
#endif

#if 0
  // Print surface directions.
  //00 Part of north surface, 01, part of east  surface, 10 part of west surface and 11 for south
  printf("Surfaces:\n");
  for(int i=0;i<(maxy*2);i+=2)
  {
    // First row, #N#
    for(int j=0;j<(maxx*2);j+=2)
    {
      if((fill2[i/2][j/2]==1) && (dir[i][j]))
      {
        printf("#%1i#",dir[i][j]);
      }
      else if(fill2[i/2][j/2]==1)
      {
        printf("###");
      }
      else
      {
        printf("   ");
      }
    }
    printf("\n");
    // Second W#E
    for(int j=0;j<(maxx*2);j+=2)
    {
      if(fill2[i/2][j/2]==1)
      {
        printf("%c#%c",dir[i+1][j]?'0'+(dir[i+1][j]%10):'#',dir[i][j+1]?'0'+(dir[i][j+1]%10):'#');
      }
      else
      {
        printf("   ");
      }
    }
    printf("\n");
    for(int j=0;j<(maxx*2);j+=2)
    {
      if((fill2[i/2][j/2]==1) && (dir[i+1][j+1]))
      {
        printf("#%1i#",dir[i+1][j+1]);
      }
      else if(fill2[i/2][j/2]==1)
      {
        printf("###");
      }
      else
      {
        printf("   ");
      }
    }
    printf("\n");
  }
#endif
  
  return;
}

int main(int argc, char* argv[])
{
  unsigned long cost = 0;
  unsigned long cost2 = 0;
  
  maxy = (sizeof(data)/sizeof(data[0]));
  maxx = strlen(data[0]);

  memset(fill,0,sizeof(fill));
  memset(area,0,sizeof(area));
  memset(per,0,sizeof(per));
  
  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      if(!fill[y][x])
      {
        fillregion(y,x);
      }
    }
  }
  for(int i=0;i<idx;i++)
  {
    cost+=area[i]*per[i];
    cost2+=area[i]*surf[i];
  }
  printf("Tot cost: %lu\n",cost);
  printf("Tot cost2: %lu\n",cost2);
  return 0;
}
