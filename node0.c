#include <stdio.h>

extern struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table 
{
  int costs[4][4];
} dt0;

#define INFINITE 999
#define NODE 4
static int neighbour[NODE] = {0,1,1,1};
static int dtcost[NODE] = {0,1,3,7};
static int dtvector0[NODE] ={0,1,3,7};
int i,j;

/* students to write the following two routines, and maybe some others */

void rtinit0() 
{
    
    for(i=0;i<NODE;i++){
        for(j=0;j<NODE;j++){
            if((i == 0)&&(neighbour[j] == 1)){
                dt0.costs[i][j] = dtcost[j];
                dt0.costs[j][i] = dtcost[j];
            }
            else
                dt0.costs[i][j] = 0;
                dt0.costs[j][i] = 0; 
            
        } 
    } 
    
    printdw(&dt0);
    struct rtpkt temp;
        temp.sourceid = 0;
    /*for(i=0;i<NODE;i++){
        if(neighbour[i]==1){
            temp.sourceid = 0;
            temp.destid = i;
        }*/
       for(j=0;j<NODE;j++){
            temp.mincost[j]=dtvector0[j];
       }
        tolayer2(temp);  
    }



void rtupdate0(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
int tempCost, vectorChange = 0;
printf("node 0 is receiving packet from node %d\n", rcvdpkt->sourceid);

for(i=0;i<NODE;i++){
    printf("%d \n",rcvdpkt->mincost[i]);
}

for(i = 0; i < NODE; i++){
  if(i != 0){
    tempCost = dtcost[rcvdpkt->sourceid] + rcvdpkt->mincost[i];
    if(tempCost < dt0.costs[i][rcvdpkt->sourceid]){
     dt0.costs[i][rcvdpkt->sourceid] = tempCost;
     printf("Node 0's distance table updated.\n");
    printdt0(&dt0);
    }
    if(tempCost < dtvector0[i]) {
     vectorChange = 1;
     dtvector0[i] = tempCost;
    }
   }
  }

  if(vectorChange == 1){
  struct rtpkt temp;
   for(i = 0; i < NODE; i++)
   {
    if(neighbour[i] == 1) {
     temp.sourceid = 0;
     temp.destid = i;
    for(j = 0;j< NODE; j++) {
     temp.mincost[i] = dtvector0[i];
    }
    printf("Packet is being sent to node %d from Node 0.\n",i);
    tolayer2(temp);
   }
   }
  printf("\n");
}
    
}


printdt0(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D0 |   0    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|   %3d  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][2],dtptr->costs[0][3]);
  printf("     1|   %3d  %3d   %3d   %3d\n",dtptr->costs[1][0],dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|   %3d  %3d   %3d   %3d\n",dtptr->costs[2][0],dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|   %3d  %3d   %3d   %3d\n",dtptr->costs[3][0],dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}

linkhandler0(linkid, newcost)   
  int linkid, newcost;

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}

  
  
  
  printdw(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D0 |   0    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|   %3d  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][2],dtptr->costs[0][3]);
  printf("     1|   %3d  %3d   %3d   %3d\n",dtptr->costs[1][0],dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|   %3d  %3d   %3d   %3d\n",dtptr->costs[2][0],dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|   %3d  %3d   %3d   %3d\n",dtptr->costs[3][0],dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}