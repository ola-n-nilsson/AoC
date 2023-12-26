#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

const long data[][6] = {
#if 1
#include "data.txt"
};
#else
#include "data2.txt"
};
#endif

#if 0
[mx,my,mz] + [msx,msy,msz]*t0 = [dx0,dy0,dz0] + [dsx0,dsy0,dsz0]*t0     7 okända
[mx,my,mz] + [msx,msy,msz]*t1 = [dx1,dy1,dz1] + [dsx1,dsy1,dsz1]*t1     7 + 1 okända
[mx,my,mz] + [msx,msy,msz]*t2 = [dx2,dy2,dz2] + [dsx2,dsy2,dsz2]*t2     7 + 2 okända
[mx,my,mz] + [msx,msy,msz]*t2 = [dx2,dy2,dz2] + [dsx2,dsy2,dsz2]*t2     7 + 2 okända
[mx,my,mz] + [msx,msy,msz]*t2 = [dx2,dy2,dz2] + [dsx2,dsy2,dsz2]*t2     7 + 2 okända

  my,my,mz,msx,msy,msz,t0,t1,t2
  mx + msx*t0 = dx0 + dsx0*t0
  my + msy*t0 = dy0 + dsy0*t0
  mz + msz*t0 = dz0 + dsz0*t0

  mx + msx*t1 = dx1 + dsx1*t1
  my + msy*t1 = dy1 + dsy1*t1
  mz + msz*t1 = dz1 + dsz1*t1

  mx + msx*t2 = dx2 + dsx2*t2
  my + msy*t2 = dy2 + dsy2*t2
  mz + msz*t2 = dz2 + dsz2*t2

#endif

  // Not so elegant, but write the script for SageMath to solve the equations...

int main(int argc, char* argv[])
{
  int cnt = 1;
  
  printf("var('mx my mz msx msy msz t1 t2 t3 ans')\n");
  for(int i=1;i<=3;i++)
  {
    printf("eq%i = mx + (msx * t%i) == %li + (%li * t%i)\n",cnt++,i,data[i][0],data[i][3],i);
    printf("eq%i = my + (msy * t%i) == %li + (%li * t%i)\n",cnt++,i,data[i][1],data[i][4],i);
    printf("eq%i = mz + (msz * t%i) == %li + (%li * t%i)\n",cnt++,i,data[i][2],data[i][5],i);
  }
  printf("eq10 = ans == mx + my + mz\n");
  printf("print(solve([eq1,eq2,eq3,eq4,eq5,eq6,eq7,eq8,eq9,eq10],mx,my,mz,msx,msy,msz,t1,t2,t3,ans))\n");
  return 0;
}


