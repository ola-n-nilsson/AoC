#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

const int data[] = {
#include "data.txt"
};

int main(int argc, char* argv[])
{
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    data[i];
  }
  return 0;
}
