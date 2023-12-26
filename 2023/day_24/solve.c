#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>



const long data[][6] = {
#if 1
#include "data.txt"
};

const long testmin = 200000000000000;
const long testmax = 400000000000000;

#else
#include "data2.txt"
};

const long testmin = 7;
const long testmax = 27;

#endif

#define X (0)
#define Y (1)
#define SX (3)
#define SY (4)

// y1 = k1x+m1
// y2 = k2x+m2
// k1 = sy1/sx1
// k2 = sy2/sx2
// n*sx1 + px1 = 0
// m1 = n*sy1 + py1
// m1 = py1 - (px1/sx1)sy1

// k1x+m1 = k2x+m2
// k1x-k2x = m2 - m1
// (k1-k2)x = m2-m1
// x = (m2-m1)/(k1-k2)


// t1 = (x-px1)/sx1

int main(int argc, char* argv[])
{
  int cnt = 0;
  
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i++)
  {
    for(int j=i+1;j<(sizeof(data)/sizeof(data[0]));j++)
    {
      if(i!=j)
      {
        double m1 = (double)data[i][Y] - (((double)data[i][X]*data[i][SY])/data[i][SX]);
        double m2 = (double)data[j][Y] - (((double)data[j][X]*data[j][SY])/data[j][SX]);
        double k1 = (double)data[i][SY]/data[i][SX];
        double k2 = (double)data[j][SY]/data[j][SX];
        double x = (m2-m1)/(k1-k2);
        double y = x*k1+m1;
        double t1 = (x-data[i][X])/data[i][SX];
        double t2 = (x-data[j][X])/data[j][SX];

        //        printf("A: %li %li\n",data[i][X],data[i][Y]);
        //        printf("B: %li %li\n",data[j][X],data[j][Y]);
        /* if(data[i][SX] == 0) */
        /* { */
        /*   printf("Divide by zero. t1 %lf\n",t1); */
        /* } */
        /* if(data[j][SX] == 0) */
        /* { */
        /*   printf("Divide by zero. t2 %lf\n",t2); */
        /* } */
        /* if((k1-k2) == 0) // Don't compare float to values.... */
        /* { */
        /*   printf("Divide by zero. x %lf\n",x); */
        /* } */
        
        if(t1>0 && t2>0 && (x<testmax && x>testmin) && (y<testmax && y>testmin))
        {
          cnt++;
          printf("%i to %i, x %lf y %lf t %lf %lf\n",i,j,x,y,t1,t2);
        }
      }
    }
  }
  printf("Cnt: %i\n",cnt);
  return 0;
}


