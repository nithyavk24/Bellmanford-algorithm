/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
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
} dt3;

#define INFINITE 999
#define NODE 4
static int neighbour[NODE] = {1,2,1,0};
static int dtcost[NODE] = {7,999,2,0};
static int dtvector3[NODE] ={7,999,2,0};
int i,j;
/* students to write the following two routines, and maybe some others */

void rtinit3() 
{
    
    for(i=0;i<NODE;i++){
        for(j=0;j<NODE;j++){
           if((i == 3)&&(neighbour[j] == 1)){
                dt3.costs[i][j] = dtcost[j];
                dt3.costs[j][i] = dtcost[j];
           }
           else if((i == 3)&&(neighbour[j] == 2)){
                dt3.costs[i][j] = INFINITE;
                dt3.costs[j][i] = INFINITE;
           }
            else{
                dt3.costs[i][j] = 0;
                dt3.costs[j][i] = 0;
            }
        } 
    }
    printdz(&dt3);
    struct rtpkt temp;
    
    for(i=0;i<NODE;i++){
        if(neighbour[i]==1){
            temp.sourceid = 3;
            temp.destid = i;
        }
        for(j=0;j<NODE;j++){
            temp.mincost[j]=dtvector3[j];
       }
        tolayer2(temp);  
    }

}


void rtupdate3(rcvdpkt)
  struct rtpkt *rcvdpkt; 
{
    static int tempCost, vectorChange = 0;
printf("node 1 is receiving packet from node %d\n", rcvdpkt->sourceid);

for(i=0;i<NODE;i++){
    printf("%d \n",rcvdpkt->mincost[i]);
}

for(i = 0; i < NODE; i++){
  if(i != 0){
    tempCost = dtcost[rcvdpkt->sourceid] + rcvdpkt->mincost[i];
    if(tempCost < dt3.costs[i][rcvdpkt->sourceid]){
     dt3.costs[i][rcvdpkt->sourceid] = tempCost;
     printf("Node 1's distance table updated.\n");
    printdt3(&dt3);
    }
    if(tempCost < dtvector3[i]) {
     vectorChange = 1;
     dtvector3[i] = tempCost;
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
     temp.mincost[j] = dtvector3[j];
    }
    printf("Packet is being sent to node %d from Node 1.\n",i);
    tolayer2(temp);
   }
   }
  printf("\n");
}

}


printdt3(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}


printdz(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D3 |   0    1     2    3 \n");
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




