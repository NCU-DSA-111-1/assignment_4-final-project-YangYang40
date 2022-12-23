#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<memory.h>
#include"file_download.h"
#define CURRENCY_NUM 19

typedef struct currency{
    char name[3];
    float rate;
}Currency_t;


void read_csv(Currency_t**currency){
    FILE *cfptr = fopen("ForeignExchangeRate","r");
    if(cfptr == NULL){
        printf("File cannot be opem\n");
    }
    
    char *row ;
    row = (char*) malloc(250);
    //currency = (Currency_t**) malloc(CURRENCY_NUM * sizeof(Currency_t*));
    int category_num = 0;
    char* token;
    int title = 0;
    while(fgets(row,250,cfptr)!=NULL){
        token = strtok(row,",");
        int count =0;
        
        while(token!= NULL){
               
            if(title == 0 && (count == 0||count ==12)){
                printf("%-15s",token);
                token = strtok(NULL,",");
            }
            else if(title!=0 && count == 0){
                
                printf("%-10s",token);
                strncpy((currency[category_num] -> name),token, 3) ;
                token = strtok(NULL,",");
                
            }
            else if(title!=0 && count == 12){
                printf("%-10s",token);
                currency[category_num] -> rate = atof(token);
                token = strtok(NULL,",");
                printf("    %d",category_num);
                category_num++;
            }
            else{
                 token = strtok(NULL,",");
            }
                
            count++;
        }

        if(title ==0){
            title = 1;
        }
        
        
        printf("\n");
    }
    
}

int main(){
    //local tine init
    time_t timep;
    struct tm *p;
    time(&timep);
    p = localtime(&timep);//get localtime

    char choice; //user choice to dowload the csv file or not
    char user_curr[57];
    Currency_t** currency;
    currency = (Currency_t**) malloc(CURRENCY_NUM * sizeof(Currency_t*));
    for(int count = 0;count<CURRENCY_NUM;count++){
        currency[count] = (Currency_t*) malloc(sizeof(Currency_t));
    }
    //currency = (Currency_t**) malloc(CURRENCY_NUM * sizeof(Currency_t*));
    printf("\nDaily Foreign Exchage Mode\n");
    printf("\nfile  \"ForeignExchangeRate\"  prepare to download\n ");
    printf("Confirm to download file (Y/N)");

    scanf("%c",&choice);
    getchar();

    //error detection
    while(choice != 'Y' && choice != 'N'){
        printf("Command wrong! please enter Y or N\n");
        scanf("%c",&choice);
        getchar();
    }

    if(choice == 'Y'){
        filedownload();
        //printf("\n-------File Download Conplete at %d-%d-%d %d:%d:%d-------\n",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday,p->tm_hour, p->tm_min, p->tm_sec);
        printf("----------File Download Complete----------");
    }
    else{
        system("clear");
    }

    //Exchange_Rate CSV file read
    
    printf("\nHere's the exchange rate for all the currency at %d-%d-%d %d:%d:%d\n",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday,p->tm_hour, p->tm_min, p->tm_sec);
    read_csv(currency);
    printf("\nPlease choose the current you want to convert:");
    scanf("%s",user_curr);
    getchar();
    for(int count = 0;count<CURRENCY_NUM;count++){
        if(strstr(user_curr,currency[count] -> name)!= NULL){
            printf("%-10s%-10.5f\n",currency[count] -> name,currency[count] -> rate);
            
        }
        
        
    }

}