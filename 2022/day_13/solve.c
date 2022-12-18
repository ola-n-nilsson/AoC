#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

typedef enum {
  STARTV,
  ENDV,
  INT,
  END
} tokentype_t;

typedef struct {
  tokentype_t type;
  int val;
} token_t;

char* data[] = {
#include "data.txt"
};

token_t parse(char** in_pp)
{
  token_t ret = {END, 0};
  
  while(**in_pp && **in_pp==',')
    (*in_pp)++;
  if(!(**in_pp))
  {
    return ret;
  }
  if(**in_pp == '[')
  {
    (*in_pp)++;
    ret.type = STARTV;
    return ret;
  }
  if(**in_pp == ']')
  {
    (*in_pp)++;
    ret.type = ENDV;
    return ret;
  }
  if(!isdigit(**in_pp))
  {
    printf("Oops\n");
    exit(-1);
  }
  ret.val = atoi(*in_pp);
  ret.type = INT;
  while(isdigit(**in_pp))
    (*in_pp)++;
  return ret;
}

int compare_strings(char* left_p, char* right_p)
{
  token_t left_tok = {STARTV, 0};
  token_t right_tok = {STARTV, 0};
  char buf[300];

  while(1)
  {
    left_tok = parse(&left_p);
    right_tok = parse(&right_p);

    if(left_tok.type == END)
    {
      return -1;
    }
    if((left_tok.type == right_tok.type) && (left_tok.val == right_tok.val))
    {
      continue;
    }
    break;
  }
  if((left_tok.type == INT) && (right_tok.type == INT))
  {
    if(left_tok.val == right_tok.val)
    {
      return 0;
    }
    if(left_tok.val < right_tok.val)
    {
      return -1;
    }
    if(left_tok.val > right_tok.val)
    {
      return 1;
    }
  }
  if((left_tok.type == INT) && (right_tok.type == STARTV))
  {
    sprintf(buf,"%i]%s",left_tok.val,left_p);
    return compare_strings(buf,right_p);
  }      
  if((right_tok.type == INT) && (left_tok.type == STARTV))
  {
    sprintf(buf,"%i]%s",right_tok.val,right_p);
    return compare_strings(left_p,buf);
  }      
  if(right_tok.type == END || right_tok.type == ENDV)
  {
    return 1;
  }
  if(left_tok.type == right_tok.type)
  {
    return 0;
  }
  return -1;
}


int main(int argc, char* argv[])
{
  int sum = 0;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=2)
  {
    char* left_p = data[i];
    char* right_p = data[i+1];
    int ret;
    
    printf("Compare: %s vs %s\n",left_p,right_p);

    ret =  compare_strings(left_p, right_p);

    if(ret != 1)
    {
      sum += ((i/2)+1);
      printf("Right order. Sum now %i\n",sum);
    }
    else
    {
      printf("Not right order.\n");
    }
  }

  printf("End with sum %i\n",sum);

  return 0;
}
