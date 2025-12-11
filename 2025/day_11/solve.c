#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#if 0
typedef enum node_t {
#include "data2d.txt"
} node_t;

node_t coni[] = {
#include "data2c.txt"
};

char* names[] = {
#include "data2s.txt"
};
#else
typedef enum node_t {
#include "datad.txt"
} node_t;

node_t coni[] = {
#include "datac.txt"
};

char* names[] = {
#include "datas.txt"
};
#endif

node_t con[1024][1024];

int visited[1024];
unsigned long pathc = 0;

void paths(node_t n)
{
  //printf("Visit %s\n",names[n]);
  if(n==out)
  {
    pathc++;
    return;
  }
  for(int idx = 1;idx<=out;idx++)
  {
    if(con[n][idx]!=NOC && !visited[idx])
    {
      //printf("from %s to %s\n",names[n],names[idx]);
      visited[idx] = 1;
      paths(idx);
      visited[idx] = 0;
    }
  }
}

int main(int argc, char* argv[])
{
  memset(con,NOC,sizeof(con));
  memset(visited,0,sizeof(visited));
  
  for(int i=0;i<(sizeof(coni)/sizeof(coni[0]));)
  {
    node_t* p = &coni[i+1];
    node_t idx = coni[i];

    i++;
    printf("Connecting node %s to: ",names[idx]);
    while(*p!=NOC)
    {
      printf("%s ",names[*p]);
      con[idx][*p] = 1;
      p++;
      i++;
    }
    i++;
    printf("\n");
  }

  visited[you] = 1;
  paths(you);
  printf("Paths: %lu\n",pathc);
  
  return 0;
}
