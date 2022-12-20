#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

const int data[] = 
#include "data.txt"
;

typedef struct node {
  long long val;
  struct node* prev_p;
  struct node* next_p;
} node_t;

node_t init_order_v[(sizeof(data)/sizeof(data[0]))+1];
int zero_pos = 0;

long long decrypt = 811589153;

void print_order(void)
{
  node_t* n_p = &init_order_v[zero_pos];
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    printf("%lli, ",n_p->val);
    n_p = n_p->next_p;
  }
  printf("\n");
}

int main(int argc, char* argv[])
{
  long long s1,s2,s3;
  
  printf("Input size: %lu\n",sizeof(data)/sizeof(data[0]));

  // Build structure;
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    init_order_v[i].val = decrypt * data[i];
    if(!data[i])
      zero_pos = i;
    if(i==0)
    {
      init_order_v[i].next_p = &init_order_v[i+1];
      init_order_v[i].prev_p = &init_order_v[((sizeof(data)/sizeof(data[0]))-1)];
    }
    else if(i==((sizeof(data)/sizeof(data[0]))-1))
    {
      init_order_v[i].next_p = &init_order_v[0];
      init_order_v[i].prev_p = &init_order_v[i-1];
    }
    else
    {
      init_order_v[i].next_p = &init_order_v[i+1];
      init_order_v[i].prev_p = &init_order_v[i-1];
    }
  }

  // Mix
  for(int j=1;j<11;j++)
  {
    for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
    {
      node_t* cur_p = &init_order_v[i];
      long long moves = init_order_v[i].val % (long long)((sizeof(data)/sizeof(data[0]))-1);
      node_t* p_p;
      node_t* n_p;

      cur_p->prev_p->next_p = cur_p->next_p;
      cur_p->next_p->prev_p = cur_p->prev_p;
      p_p = cur_p->prev_p;
      n_p = cur_p->next_p;
      if (moves < 0)
      {
        while (moves)
        {
          p_p = p_p->prev_p;
          moves++;
        }
      }
      else if (moves > 0)
      {
        while (moves)
        {
          p_p = p_p->next_p;
          moves--;
        }
      }
      n_p = p_p->next_p;
      p_p->next_p = cur_p;
      cur_p->prev_p = p_p;
      n_p->prev_p = cur_p;
      cur_p->next_p = n_p;
    }
  }

  // Start from  0
  {
    node_t* n_p = &init_order_v[zero_pos];
    int stepfor1000 = 1000 % (sizeof(data)/sizeof(data[0]));
    
    for(int j=0;j<stepfor1000;j++)
      n_p = n_p->next_p;
    printf("1000 val: %lli\n",n_p->val);
    s1 = n_p->val;
    for(int j=0;j<stepfor1000;j++)
      n_p = n_p->next_p;
    printf("2000 val: %lli\n",n_p->val);
    s2 = n_p->val;
    for(int j=0;j<stepfor1000;j++)
      n_p = n_p->next_p;
    printf("3000 val: %lli\n",n_p->val);
    s3 = n_p->val;

    printf("Sum: %lli\n",s1+s2+s3);
  }

  
  return 0;
}
