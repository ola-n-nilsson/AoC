#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#if 0
const int mdata[] = {
#include "data3b.txt"
};
#else
const int mdata[] = {
#include "datab.txt"
};
#endif

// Generate python scripts using Z3 for each system of equations

int buttons[16][16];
int bidx = 0;
int goals[16];
int gidx = 0;

int main(int argc, char* argv[])
{
  const int* lstart = &mdata[0];
  int row=1;
  
  while(*lstart>-4)
  {
    printf("Row %i\n",row);
    bidx = 0;
    gidx = 0;
    memset(buttons,0,sizeof(buttons));
    
    while(*lstart!=-2)
    {
      while(*lstart!=-1)
      {
        buttons[bidx][*lstart] = 1;
        lstart++;
      }
      bidx++;
      lstart++;
    }
    lstart++;
    while((*lstart)!=-3)
    {
      goals[gidx++] = *lstart;
      lstart++;
    }
    lstart++;

    {
      char fname[64];
      FILE* file;
      int first = 1;
      
      snprintf(fname,64,"z3_opt_%i.py",row);
      file = fopen(fname,"w+");
      fprintf(file,"from z3 import *\n\n");
      for(int j=0;j<bidx;j++)
      {
        fprintf(file,"%c = Int('%c')\n",'a'+j,'a'+j);
      }
      fprintf(file,"total = Int('total')\n\n");
      fprintf(file,"opt = Optimize()\n");
      for(int j=0;j<bidx;j++)
      {
        fprintf(file,"opt.add(%c >= 0)\n",'a'+j);
      }


      for(int j=0;j<gidx;j++)
      {
        first = 1;
        fprintf(file,"opt.add(");
        for(int k=0;k<bidx;k++)
        {
          if(buttons[k][j])
          {
            if(first)
            {
              fprintf(file,"%c",'a'+k);
              first = 0;
            }
            else
            {
              fprintf(file,"+%c",'a'+k);
            }
          }
        }
        fprintf(file,"==");
        fprintf(file,"%i",goals[j]);
        fprintf(file,")\n");
      }

      fprintf(file,"opt.add(");
      for(int j=0;j<bidx;j++)
      {
        if(j)
        {
          fprintf(file,"+%c",'a'+j);
        }
        else
        {
          fprintf(file,"%c",'a'+j);
        }
      }
      fprintf(file,"==total)\n");

      fprintf(file,"opt.minimize(total)\n");
      fprintf(file,"opt.check()\n");
      fprintf(file,"print(opt.model()[total])\n");
      
      fclose(file);
    }
    row++;
  }

  return 0;
}


