#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

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

node_t connections[1000][1000];
int cnt[1000];
int maxnode;

int compare(const void* a,const void* b)
{
  return *(int*)a-*(int*)b;
}

int main(int argc, char* argv[])
{
  maxnode = sizeof(names)/sizeof(names[0]);

  memset(connections,NOT_USED,sizeof(connections));
  memset(cnt,0,sizeof(cnt));
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=2)
  {
    connections[data[i]][data[i+1]] = 1;
    connections[data[i+1]][data[i]] = 1;
    cnt[data[i]]++;
    cnt[data[i+1]]++;
  }

  for(int n=0;n<maxnode;n++)
  {
    if(names[n][0]=='t')
    {
      node_t path[3];

      path[0]=n;
      for(int m=0;m<maxnode;m++)
      {
        if(m!=n && connections[n][m]!=NOT_USED)
        {
          path[1]=m;
          for(int q=0;q<maxnode;q++)
          {
            if(q!=n && q!=m && connections[m][q]!=NOT_USED)
            {
              path[2]=q;
              if(connections[q][n]!=NOT_USED)
              {
                node_t path2[3];

                memcpy(path2,path,sizeof(path));
                qsort(path2,3,sizeof(node_t),compare);
                printf("Loop of three: %s %s %s\n",names[path2[0]],names[path2[1]],names[path2[2]]);
              }
            }
          }
        }
      }
    }
  }
  
  return 0;
}

// and "./solve | sort | uniq | wc -l"
