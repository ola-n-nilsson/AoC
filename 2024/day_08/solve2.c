#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char* data[] = {
#include "data.txt"
};

int maxy;
int maxx;

typedef struct map_t
{
  int y;
  int x;
  struct map_t* next_p;
} map_t;

map_t* map[256];

int cnt[100][100];
int fcnt = 0;

void insert(int y,int x, int f)
{
  map_t* m = malloc(sizeof(map_t));
  map_t* p = map[f];
  
  m->y = y;
  m->x = x;
  m->next_p = NULL;

  if(map[f] == NULL)
  {
    map[f] = m;
    return;
  }
  while(p->next_p!=NULL)
  {
    p = p->next_p;
  }
  p->next_p = m;
  return;
}

int main(int argc, char* argv[])
{
  maxy = sizeof(data)/sizeof(data[0]);
  maxx = strlen(data[0]);
  memset(map,0,sizeof(map));
  memset(cnt,0,sizeof(cnt));
  
  for(int y=0;y<maxy;y++)
  {
    for(int x=0;x<maxx;x++)
    {
      if(data[y][x]!='.')
      {
        insert(y,x,data[y][x]);
      }
    }
  }

  for(int c=0;c<256;c++)
  {
    map_t *p = map[c];

    while(p)
    {
      printf("%c at %i:%i\n",c,p->y,p->x);
      p = p->next_p;
    }
  }

  {
    printf("Calc nodes:\n");

    for(int c=0;c<256;c++)
    {
      map_t *p = map[c];
      
      while(p)
      {
        map_t *p2 = p->next_p;

        while(p2)
        {
          int dy=(p->y)-(p2->y);
          int dx=(p->x)-(p2->x);
          int ny1=(p->y) + dy;
          int nx1=(p->x) + dx;
          int ny2=(p2->y) - dy;
          int nx2=(p2->x) - dx;

          // "including the antinodes that appear on every antenna" ...
          if(!cnt[p->y][p->x])
          {
            fcnt++;
          }
          cnt[p->y][p->x]++;
          if(!cnt[p2->y][p2->x])
          {
            fcnt++;
          }
          cnt[p2->y][p2->x]++;
          
          //printf("Calc %c for nodes: %i:%i %i:%i\n",c,p->y,p->x,p2->y,p2->x);
          while((ny1>=0) && (ny1<maxy) && (nx1>=0) && (nx1<maxx))
          {
            printf("Node for %c at %i:%i\n",c,ny1,nx1);
            if(!cnt[ny1][nx1])
            {
              fcnt++;
            }
            cnt[ny1][nx1]++;
            ny1=ny1 + dy;
            nx1=nx1 + dx;
            //printf("Also trying %i:%i\n",ny1,nx1);
          }
          while((ny2>=0) && (ny2<maxy) && (nx2>=0) && (nx2<maxx))
          {
            printf("Node for %c at %i:%i\n",c,ny2,nx2);
            if(!cnt[ny2][nx2])
            {
              fcnt++;
            }
            cnt[ny2][nx2]++;
            ny2=ny2 - dy;
            nx2=nx2 - dx;
            //printf("Also trying %i:%i\n",ny2,nx2);
          }
          p2 = p2->next_p;
        }
        p = p->next_p;
      }
    }
  }
  {
    for(int y=0;y<maxy;y++)
    {
      for(int x=0;x<maxx;x++)
      {
        if(cnt[y][x])
        {
          printf("#");
        }
        else
        {
          printf(".");
        }
      }
      printf("\n");
    }

  }
  printf("Count: %i\n",fcnt);
  return 0;
  
}
