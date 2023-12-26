#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#if 1
typedef enum  {
#include "datar.txt"
} node_t;

typedef struct
{
  node_t node;
  char* name;
} name_t;

const name_t names[] = {
#include "datastr.txt"
};

const node_t data[][20] = {
#include "data.txt"
};

typedef struct
{
  node_t from;
  node_t to;
} cut_t;

// Answer from boost solution in solve.cpp. Don't know enough boost to complete it there, so...
cut_t cuts[3] = {
  {sml,jbx},
  {szh,vqj},
  {vxr,zhb}};

#else
typedef enum  {
#include "datar2.txt"
} node_t;

typedef struct
{
  node_t node;
  char* name;
} name_t;

const name_t names[] = {
#include "datastr2.txt"
};

const node_t data[][20] = {
#include "data2.txt"
};

typedef struct
{
  node_t from;
  node_t to;
} cut_t;

cut_t cuts[3] = {
  {nvd,jqt},
  {bvb,cmg},
  {hfx,pzl}};

#endif

node_t graph[2048][20];
int idx[2048];
int visited[2048];

int count(node_t n)
{
  int ret = 1;
  visited[n] = 1;

  for(int i=0;i<idx[n];i++)
  {
    if(!visited[graph[n][i]])
    {
      ret += count(graph[n][i]);
    }
  }
  return ret;
}

int main(int argc, char* argv[])
{
  int guard = -1;

  memset(graph,0,sizeof(graph));
  memset(idx,0,sizeof(idx));
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    int j = 1;
    
    while(data[i][j]!=guard)
    {
      int cut = 0;
      
      for(int k=0;k<3;k++)
      {
        if((cuts[k].from == data[i][0] && cuts[k].to == data[i][j]) || (cuts[k].to == data[i][0] && cuts[k].from == data[i][j]))
        {
          cut = 1;
          break;
        }
      }
      if(!cut)
      {
        graph[data[i][0]][idx[data[i][0]]] = data[i][j];
        (idx[data[i][0]])++;
        graph[data[i][j]][idx[data[i][j]]] = data[i][0];
        (idx[data[i][j]])++;
      }
      j++;
    }
  }

  {
    int side1;
    int side2;

    memset(visited,0,sizeof(visited));
    side1 = count(cuts[0].from);
    memset(visited,0,sizeof(visited));
    side2 = count(cuts[0].to);

    printf("Sizes multiplied: %i\n",side1*side2);
  }
  
  return 0;
}
