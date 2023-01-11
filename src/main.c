#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<memory.h>
#include"namelist.h"
#include"exchange_rate.h" 
#include"store.h"
#define N 100
#define NAMELENGTH 25

/*
 * Graph is the graph representation in adjacency matrix
 */
float Graph[N][N];



typedef  char Name[NAMELENGTH];
 Name *namelst;
 // a pointer to an unknown number of arrays

// Structure to contain transaction info
//  typedef struct elements{
//     char giver[NAMELENGTH];
//     char getter[NAMELENGTH];
//     float money;
// }Elements_t;

 
 
int USER_AMOUNT, CASH_FLOW;
int u, v;
float w,tempnetcash=0,BIG,SMALL,TEMPBIG,TEMPSMALL,DIFFERENCE,fabsSMALL;
int i=0, j,k,SMALLADRESS,BIGADRESS;






void InputGraph(int b){
   
int USER_AMOUNT=b;


    

    for(k=USER_AMOUNT-1;k>0;k--)
    {
        CASH_FLOW+=2*k;
    }
 
    // Reset graph
    for(i = 0; i < USER_AMOUNT; ++i)
        for(j = 0; j < USER_AMOUNT; ++j)
            Graph[i][j] = 0;
 
    // Input Graph
    printf("Enter (user flow money):\n");
    printf("Column 1: borrower(User Number)\n");
    printf("Column 2: lender(User Number)\n");
    printf("Column 3: money\n");
    for(i = 0; i < CASH_FLOW; ++i){
        scanf("%d%d%f", &u, &v, &w);
        Graph[u][v]-=w;
        Graph[v][u]+=w;
    }

}
 
void PrintGraph(){
    // Print the current Graph
    printf("\n");
    printf("Graph:\n");
   for(i=0;i<USER_AMOUNT;i++)
   {
    printf("\t%s",namelst[i]);
   }
   printf("\n");

    for(i = 0; i < USER_AMOUNT; ++i)
    {
        printf("%s\t",namelst[i]);
    {
        for(j = 0; j < USER_AMOUNT; ++j)
            printf("%.3f\t",Graph[i][j]);
        printf("\n");
    }
    }
    printf("\n");
}
 
int main(){

    //Initialize elements
    Elements_t** elements;
    elements = (Elements_t**) malloc(50 * sizeof(Elements_t*));
    for(int count = 0;count<50;count++){
        elements[count] = (Elements_t*) malloc(sizeof(Elements_t));
    } 

    char mode;
    //main page
    printf("\n\nWelcome! which mode would you like to use?\n");
    printf("Type C for cashflow minimizer\nType E for current rate exchange\nType S to search or delete your history\nType T to turnoff\n(C/E/S/T) :");
    scanf("%c",&mode);
    getchar();
    if(mode == 'E'){
        exchange_rate();
    }
    else if(mode == 'S'){
        user_store(elements,0);
    }
    else if(mode == 'T'){
        printf("\n\nThanks for using!\n\n");
        return 1;
    }
    

 
    //Cash Flow minimizer
    printf("\n\nCash_Flow_Minimizer:\n");
    printf("============================\n\n");
    printf("Please enter user amount: ");
    scanf("%d",&USER_AMOUNT);
    namelst=makenamelist(USER_AMOUNT,namelst);
    int count =0;


    InputGraph(USER_AMOUNT);
    
    
  

    
    
    
    float NetCash[USER_AMOUNT];
    memset(NetCash, 0, sizeof(NetCash));

    for(i=0;i<USER_AMOUNT;i++)
    {
        for(j=0;j<USER_AMOUNT;j++)
        {
            NetCash[i]+=Graph[i][j];
        }
         
    }
     PrintGraph();

    for(i=0;i<USER_AMOUNT;i++)
    {
        printf("Netcash for %s: %.3f\n",namelst[i],NetCash[i]);
    }
    BIG=NetCash[0];
    SMALL=NetCash[0];
  
    
   
  
    do
    {
          for(i=0;i<USER_AMOUNT;i++)
        {if(SMALL>NetCash[i])
            {SMALL=NetCash[i];
            SMALLADRESS=i;}
        }
        fabsSMALL=fabs(SMALL);
    for(j=0;j<USER_AMOUNT;j++)
        {if(BIG<NetCash[j])
            {BIG=NetCash[j];
            BIGADRESS=j;}
        }
    DIFFERENCE=BIG-fabsSMALL;

    if(DIFFERENCE>0)
    {
        printf("%s should pay %s %f dollars\n",namelst[SMALLADRESS],namelst[BIGADRESS],fabsSMALL);
        //store
        strncpy((elements[count] -> giver),namelst[SMALLADRESS],NAMELENGTH);
        strncpy((elements[count] -> getter),namelst[BIGADRESS],NAMELENGTH);
        elements[count] -> money = fabs(fabsSMALL);
        //printf("%s,%s,%f\n",elements[count] -> giver,elements[count] -> getter,elements[count] -> money);
        count++;

        NetCash[BIGADRESS]=DIFFERENCE;
        NetCash[SMALLADRESS]=0;
        SMALL=0;
        BIG=0;
    }

   else if(DIFFERENCE<0)
    {
        printf("%s should pay %s %f dollars\n",namelst[SMALLADRESS],namelst[BIGADRESS],BIG);
        //store
        strncpy((elements[count] -> giver),namelst[SMALLADRESS],NAMELENGTH);
        strncpy((elements[count] -> getter),namelst[BIGADRESS],NAMELENGTH);
        elements[count] -> money = fabs(BIG);
        //printf("%s,%s,%f\n",elements[count] -> giver,elements[count] -> getter,elements[count] -> money);
        count++;

        NetCash[SMALLADRESS]=DIFFERENCE;
        NetCash[BIGADRESS]=0;
        BIG=0;
        SMALL=0;
    }
    else if(DIFFERENCE==0)
    {
    printf("%s should pay %s %f dollars\n",namelst[SMALLADRESS],namelst[BIGADRESS],BIG);
    //store
    strncpy((elements[count] -> giver),namelst[SMALLADRESS],NAMELENGTH);
    strncpy((elements[count] -> getter),namelst[BIGADRESS],NAMELENGTH);
    elements[count] -> money = fabs(fabsSMALL);
    //printf("%s,%s,%f\n",elements[count] -> giver,elements[count] -> getter,elements[count] -> money);
    count++;

    NetCash[SMALLADRESS]=0;
    NetCash[BIGADRESS]=0;
    BIG=0;
    SMALL=0;
    for(i=0;i<USER_AMOUNT;i++)
        {if(SMALL>NetCash[i])
            {SMALL=NetCash[i];
            SMALLADRESS=i;}
        }
        fabsSMALL=fabs(SMALL);
    for(j=0;j<USER_AMOUNT;j++)
        {if(BIG<NetCash[j])
            {BIG=NetCash[j];
            BIGADRESS=j;}
    }
    }
    } while (NetCash[SMALLADRESS]!=0||NetCash[BIGADRESS]!=0);
    
    printf("\n\n ---finish recordding--- \n\n");
    user_store(elements,count);

   
 
    return 0;
}