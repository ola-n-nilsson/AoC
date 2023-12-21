#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
  int sy;
  int sx;
  int stop;
  int cnt;
  char type;
} tile_t;

/* Tile type J count: 7474 */
/* Tile type U count: 7407 */
/* Tile type N count: 5572 */
/* Tile type E count: 5577 */
/* Tile type S count: 5577 */
/* Tile type W count: 5572 */
/* Tile type 1 count: 942 */
/* Tile type 2 count: 6479 */
/* Tile type 3 count: 939 */
/* Tile type 4 count: 6500 */
/* Tile type 5 count: 953 */
/* Tile type 6 count: 6484 */
/* Tile type 7 count: 958 */
/* Tile type 8 count: 6500 */

enum {
  J = 0,
  U,
  N,
  E,
  S,
  W,
  S1,
  S2,
  S3,
  S4,
  S5,
  S6,
  S7,
  S8
};

tile_t tiles[] = {
  { 65,65,130,7474,'J'},
  { 65,65,131,7407,'U'},
  { 130,65,130,5572,'N'},
  { 65,0,130,5577,'E'},
  { 0,65,130,5577,'S'},
  { 65,130,130,5572,'W'},
  { 130,130,64,942,'1'},
  { 130,130,195,6479,'2'},
  { 130,0,64,939,'3'},
  { 130,0,195,6500,'4'},
  { 0,0,64,953,'5'},
  { 0,0,195,6484,'6'},
  { 0,130,64,958,'7'},
  { 0,130,195,6500,'8'}
};

char* data[] = {
#include "dataus.txt"
};

int maxy;
int maxx;

char visited[256][256];
int nexty[256*256];
int nextx[256*256];
int nextidx;

int prepy[256*256];
int prepx[256*256];
int idx;

void insert(int y, int x)
{
  int i;
  
  for(i=0;i<idx;i++)
  {
    if((prepy[i]==y) && (prepx[i]==x))
    {
      return;
    }
  }
  prepy[i]=y;
  prepx[i]=x;
  idx++;
  return;
}

void walk(int step,int stop)
{
  
  if(step==stop)
  {
    // Don't walk any more.
    for(int i=0;i<nextidx;i++)
    {
      visited[nexty[i]][nextx[i]] = 'O';
    }
    return;
  }

  // Walk
  {
    int y;
    int x;
    
    for(int i=0;i<nextidx;i++)
    {
      y = nexty[i];
      x = nextx[i];
      if(y && ((data[y-1][x]=='.') || (data[y-1][x]=='S')) && ((!(visited[y-1][x]))))
      {
        //        printf("At step %i visit %i:%i\n",step,y-1,x);
        insert(y-1,x);
      }
      if(x && ((data[y][x-1]=='.') || (data[y][x-1]=='S')) && (!(visited[y][x-1])))
      {
        //        printf("At step %i visit %i:%i\n",step,y,x-1);
        insert(y,x-1);
      }
      if(((y+1)<maxy) && ((data[y+1][x]=='.') || (data[y+1][x]=='S')) && ((!(visited[y+1][x]))))
      {
        //        printf("At step %i visit %i:%i\n",step,y+1,x);
        insert(y+1,x);
      }
      if(((x+1)<maxx) && ((data[y][x+1]=='.') || (data[y][x+1]=='S')) && ((!(visited[y][x+1]))))
      {
        //        printf("At step %i visit %i:%i\n",step,y,x+1);
        insert(y,x+1);
      }
    }
  }
  step++;
  memcpy(nexty,prepy,sizeof(int)*idx);
  memcpy(nextx,prepx,sizeof(int)*idx);
  nextidx = idx;
  idx = 0;
  walk(step,stop);
}


int main(int argc, char* argv[])
{
  int precalc = 1;
  maxy = sizeof(data)/sizeof(data[0]);
  maxx = strlen(data[0]);

  for(int j=0;j<(sizeof(tiles)/sizeof(tiles[0])) && !precalc;j++)
  {
    int starty = tiles[j].sy;
    int startx = tiles[j].sx;

    memset(visited,0,sizeof(visited));
  
    printf("Field size: %i:%i Start: %i,%i\n",maxy,maxx,starty,startx);

    nexty[0] = starty;
    nextx[0] = startx;
    nextidx = 1;
    idx = 0;
    
    walk(0,tiles[j].stop);

    {
      int cnt = 0;

      for(int y=0;y<maxy;y++)
      {
        for(int x=0;x<maxx;x++)
        {
          if(visited[y][x] == 'O')
          {
            printf("O");
            cnt++;
          }
          else
          {
            printf("%c",data[y][x]);
          }
        }
        printf("\n");
      }
      tiles[j].cnt = cnt;
      printf("Tile type %c count: %i\n",tiles[j].type,cnt);
    }
  }

  {
    unsigned long pos = 0;
    unsigned long nbr = 202300;
    
    pos += tiles[N].cnt;
    pos += tiles[S].cnt;
    pos += tiles[W].cnt;
    pos += tiles[E].cnt;

    
    pos += ((unsigned long)tiles[S1].cnt) * nbr;
    pos += ((unsigned long)tiles[S2].cnt) * (nbr-1);
    pos += ((unsigned long)tiles[S3].cnt) * nbr;
    pos += ((unsigned long)tiles[S4].cnt) * (nbr-1);
    pos += ((unsigned long)tiles[S5].cnt) * nbr;
    pos += ((unsigned long)tiles[S6].cnt) * (nbr-1);
    pos += ((unsigned long)tiles[S7].cnt) * nbr;
    pos += ((unsigned long)tiles[S8].cnt) * (nbr-1);

    pos += ((unsigned long)tiles[U].cnt) * ((unsigned long)(nbr-1)*(unsigned long)(nbr-1));
    pos += ((unsigned long)tiles[J].cnt) * (((unsigned long)(nbr) * (unsigned long)(nbr)));

    printf("Positions: %lu\n",pos);
  }

  return 0;
}

#if 0

	n=4	 n=6	 n=8	General
J	 16	  36	  64	n^2
U	  9	  25	  49	(n-1)^2
N	  1	   1	   1	1
E	  1	   1	   1	1
S	  1	   1	   1	1
W	  1	   1	   1	1
S1	4	   6	   8	n
S2	3	   5	   7	n-1
S3	4	   6	   8	n
S4	3	   5	   7	n-1
S5	4	   6	   8	n
S6	3	   5	   7	n-1
S7	4	   6	   8	n
S8	3	   5	   7	n-1


n=4
          1N3
         12J43
        12JUJ43
       12JUJUJ43
       WJUJUJUJE
       78JUJUJ65
        78JUJ65
         78J65
          7S5
n=6
          1N3
         12J43
        12JUJ43
       12JUJUJ43
      12JUJUJUJ43
     12JUJUJUJUJ43
     WJUJUJUJUJUJE
     78JUJUJUJUJ65
      78JUJUJUJ65
       78JUJUJ65
        78JUJ65
         78J65
          7S5
n=8
  
          1N3
         12J43
        12JUJ43
       12JUJUJ43
      12JUJUJUJ43
     12JUJUJUJUJ43
    12JUJUJUJUJUJ43
   12JUJUJUJUJUJUJ43
   WJUJUJUJUJUJUJUJE
   78JUJUJUJUJUJUJ65
    78JUJUJUJUJUJ65
     78JUJUJUJUJ65
      78JUJUJUJ65
       78JUJUJ65
        78JUJ65
         78J65
          7S5

n=10
          1N3
         12J43
        12JUJ43
       12JUJUJ43
      12JUJUJUJ43
     12JUJUJUJUJ43
    12JUJUJUJUJUJ43
   12JUJUJUJUJUJUJ43
  12JUJUJUJUJUJUJUJ43
 12JUJUJUJUJUJUJUJUJ43
 WJUJUJUJUJUJUJUJUJUJE
 78JUJUJUJUJUJUJUJUJ65
  78JUJUJUJUJUJUJUJ65
   78JUJUJUJUJUJUJ65
    78JUJUJUJUJUJ65
     78JUJUJUJUJ65
      78JUJUJUJ65
       78JUJUJ65
        78JUJ65
         78J65
          7S5

  
#endif


