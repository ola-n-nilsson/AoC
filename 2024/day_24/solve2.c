#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef enum op_t {
  OR = 0,
  AND,
  XOR
} op_t;

typedef enum wire_t {
#include "nodes.txt"
} wire_t;

int data[] = {
#include "data.txt"
};

char* names[] = {
#include "names.txt"
};

int values[512];

void initvalues(void)
{
#include "start.txt"
}

char* carry[] = {
  "c00",
  "c01",
  "c02",
  "c03",
  "c04",
  "c05",
  "c06",
  "c07",
  "c08",
  "c09",
  "c10",
  "c11",
  "c12",
  "c13",
  "c14",
  "c15",
  "c16",
  "c17",
  "c18",
  "c19",
  "c20",
  "c21",
  "c22",
  "c23",
  "c24",
  "c25",
  "c26",
  "c27",
  "c28",
  "c29",
  "c30",
  "c31",
  "c32",
  "c33",
  "c34",
  "c35",
  "c36",
  "c37",
  "c38",
  "c39",
  "c40",
  "c41",
  "c42",
  "c43",
  "c44"
};

char* result[] = {
  "r00",
  "r01",
  "r02",
  "r03",
  "r04",
  "r05",
  "r06",
  "r07",
  "r08",
  "r09",
  "r10",
  "r11",
  "r12",
  "r13",
  "r14",
  "r15",
  "r16",
  "r17",
  "r18",
  "r19",
  "r20",
  "r21",
  "r22",
  "r23",
  "r24",
  "r25",
  "r26",
  "r27",
  "r28",
  "r29",
  "r30",
  "r31",
  "r32",
  "r33",
  "r34",
  "r35",
  "r36",
  "r37",
  "r38",
  "r39",
  "r40",
  "r41",
  "r42",
  "r43",
  "r44"
};

int main(int argc, char* argv[])
{
  memset(values,-1,sizeof(values));
  initvalues();

  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=4)
  {
    // Sort all arguments
    if(data[i]>data[i+2])
    {
      int d = data[i];
      data[i] = data[i+2];
      data[i+2] = d;
    }
  }
  //Rename all carry for bits 1--44
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=4)
  {
    if(data[i]>=x00 && data[i]<=x44)
    {
      if(data[i+2]>=y00 && data[i+2]<=y44)
      {
        if(data[i+1]==AND)
        {
          if(data[i]-x00 != data[i+2]-y00)
          {
            printf("Look at AND for %s\n",names[data[i]]);
          }
          printf("Renaming %s to %s\n",names[data[i+3]],carry[data[i]-x00]);
          names[data[i+3]] = carry[data[i]-x00];
        }
      }
    }
  }
  //Rename all result bits
  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=4)
  {
    if(data[i]>x00 && data[i]<=x44)
    {
      if(data[i+2]>y00 && data[i+2]<=y44)
      {
        if(data[i+1]==XOR)
        {
          if(data[i]-x00 != data[i+2]-y00)
          {
            printf("Look at XOR for %s\n",names[data[i]]);
          }
          printf("Renaming %s to %s\n",names[data[i+3]],result[data[i]-x00]);
          names[data[i+3]] = result[data[i]-x00];
        }
      }
    }
  }

  for(int i=0;i<(sizeof(data)/sizeof(data[0]));i+=4)
  {
    printf("%s ",names[data[i]]);
    switch(data[i+1])
    {
      case OR:
        printf("OR ");
        break;
      case AND:
        printf("AND ");
        break;
      case XOR:
        printf("XOR ");
        break;
    }
    printf("%s -> %s\n",names[data[i+2]],names[data[i+3]]);
  }
  
  return 0;
}

// It helps to look at the heladderare here: https://sv.wikipedia.org/wiki/Adderare

// Looking at the output shows (after some filtering):
// We have exactly four strange patterns
#if 0
c14 XOR scs -> z14  <- Missing r14, but c14 is here
r01 XOR c00 -> z01
r02 XOR rwp -> z02
r03 XOR fmj -> z03
r04 XOR ncp -> z04
r05 XOR qfj -> z05
r06 XOR hjm -> z06
r07 XOR tnr -> z07
r08 XOR sjd -> mvb <- Looks bad
r09 XOR ggm -> z09
r10 XOR kdf -> z10
r11 XOR rcq -> z11
r12 XOR snr -> z12
r13 XOR fmk -> z13
r15 XOR tsg -> z15
r16 XOR qhk -> z16
r17 XOR qfp -> z17
r18 XOR mfk -> wss <- Looks bad
r19 XOR nws -> z19
r20 XOR qpn -> z20
r21 XOR gkw -> z21
r22 XOR qtq -> z22
r23 XOR bpr -> bmn <- Looks bad
r24 XOR bmn -> z24
r25 XOR jvg -> z25
r26 XOR vhm -> z26
r27 XOR jbg -> z27
r28 XOR mgv -> z28
r29 XOR wfr -> z29
r30 XOR rqd -> z30
r31 XOR bvv -> z31
r32 XOR shr -> z32
r33 XOR mqb -> z33
r34 XOR smq -> z34
r35 XOR prv -> z35
r36 XOR vvt -> z36
r37 XOR jrs -> z37
r38 XOR chf -> z38
r39 XOR wch -> z39
r40 XOR sfr -> z40
r41 XOR rmb -> z41
r42 XOR vcr -> z42
r43 XOR mvj -> z43
r44 XOR sgh -> z44
#endif 

// c14 and r14
// Renaming rds to c14
// Renaming jss to r14
// = rds och jss
// mvb and z08
// wss and z18
// bmn and z23


// bmn,jss,mvb,rds,wss,z08,z18,z23 which was right!
