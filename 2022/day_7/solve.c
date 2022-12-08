#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define OP_CD -1
#define OP_LS -2
#define OP_END -3
#define OP_CD_BACK -4

typedef struct {
  int op_or_size;
  char* name;
} op_t;

const op_t data[] = {
#include "data.txt"
};

unsigned long dir_size(int* i,char* name)
{
  unsigned long size = 0;
  char new_name[1024];

  //  printf("ola: ls of: %s\n",name);
  while((data[*i].op_or_size != OP_END) &&
        (data[*i].op_or_size != OP_CD_BACK))
  {
    if(data[*i].op_or_size == OP_LS)
    {
      (*i)++;
      size += dir_size(i,new_name);
    }
    else if(data[*i].op_or_size == OP_CD)
    {
      strcpy(new_name,name);
      strcat(new_name,data[*i].name);
      strcat(new_name,"/");
      (*i)++;
    }
    else
    {
      size += data[*i].op_or_size;
      (*i)++;
    }
  }
  if(data[*i].op_or_size == OP_CD_BACK)
  {
    //    printf("ola: cd back\n");
    (*i)++;
  }
  printf("%lu %s\n",size,name);
  return size;
}

int main(int argc, char* argv[])
{
  int i = 3;
  char name[] = "/";
  
  (void)dir_size(&i,name);

  return 0;
}
