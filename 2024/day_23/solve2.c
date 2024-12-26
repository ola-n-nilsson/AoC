#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#if 0
typedef enum node_t {
  NOT_USED=-1,
#include "node2.txt"
} node_t;

char* names[] = {
#include "nodenames2.txt"
};

node_t data[] = {
#include "data2.txt"
};
#else
typedef enum node_t {
  NOT_USED=-1,
#include "node.txt"
} node_t;

char* names[] = {
#include "nodenames.txt"
};

node_t data[] = {
#include "data.txt"
};
#endif

node_t connections[1000][1000];
int cnt[1000];
int maxnode;
int nv[1000][16];
int nvidx[1000];

int maxlen = 0;

int compare(const void* a,const void* b)
{
  return *(int*)a-*(int*)b;
}

/*
algorithm BronKerbosch1(R, P, X) is
    if P and X are both empty then
        report R as a maximal clique
    for each vertex v in P do
        BronKerbosch1(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
        P := P \ {v}
        X := X ⋃ {v}

   From: https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
 */
void BronKerbosch1(int* r, int ri, int* p, int pi, int* x, int xi)
{
  /*
  printf("BK: r ");
  printf("(");
  for(int i=0;i<ri;i++)
    printf("%s ",names[r[i]]);
  printf(") ");
  printf("len %i p ",ri);
  if(pi<15)
  {
    printf("(");
    for(int i=0;i<pi;i++)
      printf("%s ",names[p[i]]);
    printf(") ");
  }
  else
  {
    printf("(...) ");
  }
  printf("len %i x",pi);
  if(xi<15)
  {
    printf("(");
    for(int i=0;i<xi;i++)
      printf("%s ",names[x[i]]);
    printf(") ");
  }
  else
  {
    printf("(...) ");
  }
  printf("len %i\n",xi);
  */
  
  if(!xi && !pi && (ri>maxlen))
  {
    maxlen = ri;
    printf("Found len %i: ",ri);
    for(int i=0;i<ri;i++)
    {
      printf("%s ",names[r[i]]);
    }
    printf(".\n");
    return;
  }
  {
    int nr[16];
    memcpy(nr,r,sizeof(int)*ri);
    
    for(int pidx=0;pidx<pi;pidx++)
    {
      int np[16];
      int nx[16];
      int npidx = 0;
      int nxidx = 0;
      
      nr[ri] = p[pidx];
      for(int ip=pidx;ip<pi;ip++)  // This is where we remove p's that has been moved to x
      {
        for(int neidx=0;neidx<nvidx[p[pidx]];neidx++)
        {
          if(p[ip]==nv[p[pidx]][neidx])
          {
            np[npidx++] = p[ip];
            continue;
          }
        }
      }
      for(int ix=0;ix<xi;ix++)
      {
        for(int neidx=0;neidx<nvidx[p[pidx]];neidx++)
        {
          if(x[ix]==nv[p[pidx]][neidx])
          {
            nx[nxidx++] = x[ix];
            continue;
          }
        }
      }
      BronKerbosch1(nr,ri+1,np,npidx,nx,nxidx);
      x[xi++]=p[pidx];
    }
  }
}

int main(int argc, char* argv[])
{
  maxnode = sizeof(names)/sizeof(names[0]);

  memset(connections,NOT_USED,sizeof(connections));
  memset(cnt,0,sizeof(cnt));
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=2)
  {
    if(connections[data[i]][data[i+1]]!=1)
    {
      connections[data[i]][data[i+1]] = 1;
      cnt[data[i]]++;
    }
    if(connections[data[i+1]][data[i]]!=1)
    {
      connections[data[i+1]][data[i]] = 1;
      cnt[data[i+1]]++;
    }
  }

  //Restructure the neighbouring sets
  memset(nv,0,sizeof(nv));
  memset(nvidx,0,sizeof(nvidx));
  for(int n=0;n<maxnode;n++)
  {
    for(int m=0;m<maxnode;m++)
    {
      if(n!=m && connections[n][m] != NOT_USED)
      {
        nv[n][nvidx[n]++] = m;
      }
    }
  }
  /*
  for(int n=0;n<maxnode;n++)
  {
    if(nvidx[n]>10)
    {
      printf("%s neighbour: ",names[n]);
      for(int i=0;i<nvidx[n];i++)
      {
        printf("%s ",names[nv[n][i]]);
      }
      printf("\n");
    }
  }  
  printf("\n");
  */
  
  {
    int cand[1000];
    int cidx = 0;
    int cliq[16];
    int qidx = 0;
    int ex[1000];
    int xidx = 0;
    
    for(int n=0;n<maxnode;n++)
    {
      cand[cidx++] = n;
    }
    BronKerbosch1(cliq,qidx,cand,cidx,ex,xidx);
  }
 
  return 0;
}

