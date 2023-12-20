#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef enum {
#include "datar.txt"
} module_t;

typedef struct {
  module_t m;
  char* name;
} m2name_t;

m2name_t names[] = {
#include "datastr.txt"
};

typedef struct {
  module_t m;
  char type;
} mtype_t;

mtype_t mtype[] = {
#include "datat.txt"
};

#define DESTSIZE (20)
module_t map[][DESTSIZE] = {
#include "data.txt"
};

#define CONVSIZE (16)
int flips[end];
int conv[end][CONVSIZE];
module_t convfrom[end][CONVSIZE];
int convidx [end];
                   
unsigned long highcnt = 0;
unsigned long lowcnt = 0;

typedef struct {
  module_t src;
  module_t dest;
  int high;
} pulsq_t;

#define QSIZE (50000)
pulsq_t queue[QSIZE];
int qridx = 0;
int qwidx = 0;

unsigned long buttons = 1;

unsigned long gp_period = 0;
unsigned long rb_period = 0;
unsigned long ml_period = 0;
unsigned long bt_period = 0;

void send(module_t dest,module_t src, int high)
{
  //  printf("%s -%s-> %s\n",names[src].name,high?"high":"low",names[dest].name);
  if(src==gp && !high)
  {
    if(!gp_period)
    {
      gp_period = buttons;
    }
    printf("GP low signal at %lu buttons\n",buttons);
  }
  else if(src==rb && !high)
  {
    if(!rb_period)
    {
      rb_period = buttons;
    }
    printf("RB low signal at %lu buttons\n",buttons);
  }
  else if(src==ml && !high)
  {
    if(!ml_period)
    {
      ml_period = buttons;
    }
    printf("ML low signal at %lu buttons\n",buttons);
  }
  else if(src==bt && !high)
  {
    if(!bt_period)
    {
      bt_period = buttons;
    }
    printf("BT low signal at %lu buttons\n",buttons);
  }
  if(high)
  {
    highcnt++;
  }
  else
  {
    lowcnt++;
  }
  queue[qwidx].src = src;
  queue[qwidx].dest = dest;
  queue[qwidx].high = high;
  qwidx = (qwidx+1) % QSIZE;
  if(qwidx==qridx)
  {
    printf("Oopsa!\n");
    exit(-1);
  }
}

void get(module_t* dest_p,module_t* src_p,int* high_p)
{
  if(qridx == qwidx)
  {
    *src_p = guard;
    *dest_p = end;
    *high_p = 0;
  }
  else
  {
    *src_p = queue[qridx].src;
    *dest_p = queue[qridx].dest;
    *high_p = queue[qridx].high;
    qridx = (qridx+1) % QSIZE;
  }
}

int empty(void)
{
  return qridx == qwidx;
}

void printstate(module_t m)
{
  if(mtype[m].type == '&')
  {
    int state = 0;
    
    for(int i=0;i<convidx[m];i++)
    {
      state = state<<1;
      if(conv[m][i])
      {
        state |= 1;
      }
    }
    printf("%s: %i\n",names[m].name,state);
  }
}

int getstate(module_t m)
{
  if(mtype[m].type == '&')
  {
    int state = 0;
    
    for(int i=0;i<convidx[m];i++)
    {
      state = state<<1;
      if(conv[m][i])
      {
        state |= 1;
      }
    }
    return state;
  }
  return 1;
}

int main(int argc, char* argv[])
{
  memset(flips,0,sizeof(flips));
  memset(conv,0,sizeof(conv));
  memset(convfrom,0,sizeof(convfrom));
  memset(convidx,0,sizeof(convidx));
    
  for(int i=0;i<(sizeof(map)/sizeof(map[0]));i++)
  {
    int j=1;
    printf("%s to: ",names[map[i][0]].name);
    while(map[i][j])
    {
      printf("%s, ",names[map[i][j]].name);
      j++;
    }
    printf("\n");
  }

  // Could have been done in the print loop, but for clarity. Initialize inputs to conjunction modules
  for(int i=0;i<(sizeof(map)/sizeof(map[0]));i++)
  {
    int j=1;

    while(map[i][j])
    {
      if(mtype[map[i][j]].type == '&')
      {
        printf("Input to %s from %s\n",names[i].name,names[map[i][j]].name);
        convfrom[map[i][j]][convidx[map[i][j]]] = i;
        (convidx[map[i][j]])++;
      }
      j++;
    }
  }

  while(!gp_period || !rb_period || !ml_period || !bt_period)
  {
    module_t src;
    module_t dest;
    int high;
    
    send(broadcaster,end,0);
    do
    {
      get(&dest,&src,&high);
      switch(mtype[dest].type)
      {
        case '%':
          if(!high)
          {
            flips[dest] = !flips[dest];

            for(int j=1;j<DESTSIZE;j++)
            {
              if(map[dest][j] != guard)
              {
                send(map[dest][j],dest,flips[dest]);
              }
              else
              {
                break;
              }
            }
          }
          break;
        case '&':
          {
            int lochigh = 0;
            int j;
            
            // Check if we have recived from this sender before
            for(j=0;j<convidx[dest];j++) 
            {
              if(convfrom[dest][j]==src)
              {
                break;
              }
            }
            if(j<convidx[dest])
            {
              // printf("%s recived %s from %s and it was found.\n",names[dest].name,high?"high":"low",names[src].name);
              conv[dest][j] = high;
            }
            else
            {
              printf("Oops, missed an input to & in prep\n");
              exit(-1);
            }
            for(j=0;j<convidx[dest];j++) 
            {
              if(!(conv[dest][j]))
              {
                lochigh = 1;
                break;
              }
            }
            for(j=1;j<DESTSIZE;j++)
            {
              if(map[dest][j] != guard)
              {
                send(map[dest][j],dest,lochigh);
              }
              else
              {
                break;
              }
            }
          }
          break;
        case 'b':
          for(int j=1;j<DESTSIZE;j++)
          {
            if(map[dest][j] != guard)
            {
              send(map[dest][j],dest,high);
            }
            else
            {
              break;
            }
          }
          break;
        case 'S':
          // I had one module that was just a destination. Lets sink thoose signals
          if(!high)
          {
            printf("Low to rx after %lu buttons\n",buttons);
            exit(0);
          }
          break;
        case 'g':
        case 'e':
        default:
          printf("Oops!\n");
          exit(-1);
          break;
          
      }
    } while(!empty());
    buttons++;
  }

  printf("gp_period %lu rb_period %lu ml_period %lu bt_period %lu\n mul: %lu\n",gp_period,rb_period,ml_period,bt_period, gp_period*rb_period*ml_period*bt_period);
  
  return 0;
}


