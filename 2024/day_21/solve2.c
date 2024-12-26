#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

// Done the numpad seperatly and now just take all alternatives for dirpad

char* data[] = {
#include "data_af.txt"
};

/*
    +---+---+
    | ^ | A |
+---+---+---+
| < | v | > |
+---+---+---+
*/

// Delta to get to and from a pair
int dy[256][256];
int dx[256][256];

// Coorinates on the pad for char
int sy[256];
int sx[256];

/*
int dirlens[256][256];

void init_dirlens(void)
{
  ['^']['^'] = 1; // A
}
*/

unsigned long cache[256][256][30];

void init(void)
{
  memset(sy,-1,sizeof(sy));
  memset(sx,-1,sizeof(sx));
  memset(cache,-1,sizeof(cache));
  
  sy[(int)'A'] = 0;
  sy[(int)'^'] = 0;
  sy[(int)'X'] = 0;
  sy[(int)'<'] = 1;
  sy[(int)'v'] = 1;
  sy[(int)'>'] = 1;
  sx[(int)'A'] = 2;
  sx[(int)'^'] = 1;
  sy[(int)'X'] = 0;
  sx[(int)'<'] = 0;
  sx[(int)'v'] = 1;
  sx[(int)'>'] = 2;
  
  memset(dy,0,sizeof(dy));
  memset(dx,0,sizeof(dx));
  for(int c1=0;c1<256;c1++)
  {
    for(int c2=0;c2<256;c2++)
    {
      if(sy[c1]!=-1 && sy[c2]!=-1)
      {
        dx[c1][c2] = sx[c1]-sx[c2];
        dy[c1][c2] = sy[c1]-sy[c2];
      }
    }
  }
}


int dirpada(int from, int to,int dir,char *p)
{
  int y=sy[from];
  int x=sx[from];
  int ey=sy[to];
  int ex=sx[to];
  int len = 0;

  //     +---+---+
  //     | ^ | A |
  // +---+---+---+
  // | < | v | > |
  // +---+---+---+

  // If we would hit the X, then change dir
  if(dir)
  {
    // if y=0 and we target x = 0, we would hit
    // if x=0 and we target y = 0, we would hit
    if(y==0 && ex==0)
    {
      *p = '\0';
      return 0;
    }
  }
  else
  {
    if(x==0 && ey==0)
    {
      *p = '\0';
      return 0;
    }
  }
  
  if(dir)
  {
    while(x<ex) // right
    {
      *p++ = '>';
      len++;
      x++;
    }
    while(x>ex) // left
    {
      *p++ = '<';
      len++;
      x--;
    }
  }
  while(y<ey) // down
  {
    *p++ = 'v';
    len++;
    y++;
  }
  while(y>ey) // up
  {
    *p++ = '^';
    len++;
    y--;
  }
  if(!dir)
  {
    while(x<ex) // right
    {
      *p++ = '>';
      len++;
      x++;
    }
    while(x>ex) // left
    {
      *p++ = '<';
      len++;
      x--;
    }
  }
  
  *p++ = 'A';
  len++;

  *p = '\0';
  return len;
}

unsigned long bestlength(char* p, int level);


unsigned long bestlengthpair(int from, int to, int level)
{
  // Sum the bestlengthpair that is needed for each move one level up.
  int ldx = dx[from][to];
  int ldy = dy[from][to];
  unsigned long ret = (unsigned long)-1;
  char path[64];

  //printf("Blp: %c to %c %i\n",from,to,level);

  
  if(cache[from][to][level]!=-1)
  {
    return cache[from][to][level];
  }
  if(ldx && ldy)
  {
    unsigned long ret2 = (unsigned long)-1;
    int len;
    int len2;
    
    // We might have to try two different paths
    len = dirpada(from,to,0,path);
    if(len)
    {
      ret = bestlength(path,level+1);
    }
    len2 = dirpada(from,to,1,path);
    if(len2)
    {
      ret2 = bestlength(path,level+1);
    }
    if(len && len2)
    {
      if(ret2<ret)
      {
        ret = ret2;
      }
    }
    else if(len2)
    {
      ret = ret2;
    }
  }
  else
  {
    int len;

    len = dirpada(from,to,0,path);
    if(!len)
    {
      printf("Oops!\n");
      exit(-1);
    }
    ret = bestlength(path,level+1);
  }
  cache[from][to][level] = ret;
  return ret;
}

unsigned long bestlength(char* p, int level)
{
  int moves[256][256];
  unsigned long ret = 0;

  //printf("Bl: %s %i\n",p,level);
  
  if(level==26)
  {
    return strlen(p);
  }
  
  memset(moves,0,sizeof(moves));
  if(*p)
  {
    moves[(int)'A'][(int)*p]++;
  }
  while(*p && p[1])
  {
    moves[(int)p[0]][(int)p[1]]++;
    p++;
  }

  for(int c1=0;c1<256;c1++)
  {
    for(int c2=0;c2<256;c2++)
    {
      if(moves[c1][c2])
      {
        ret += bestlengthpair(c1,c2,level) * moves[c1][c2];
      }
    }
  }
  return ret;
}

int main(int argc, char* argv[])
{
  unsigned long min[1000];
  unsigned long mul = 0;
  
  init();

  memset(min,0,sizeof(min));
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=2)
  {
    unsigned long len = 0;
    int nbr;
    
    printf("Trying for %s with first level %s\n",data[i],data[i+1]);

    sscanf(data[i],"%d",&nbr);
    len = bestlength(data[i+1],1);

    if(!min[nbr])
    {
      min[nbr] = len;
    }
    else
    {
      if(len<min[nbr])
      {
        min[nbr] = len;
      }
    }
    printf("Length: %lu\n",len);
  }

  for(int i=0;i<1000;i++)
  {
    if(min[i])
    {
      printf("Min for %03i: %lu\n",i,min[i]);
      mul += min[i]*i;
    }
  }
  printf("Mul: %lu\n",mul);
  
  return 0;
}
