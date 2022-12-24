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

void choose_currency(Currency_t**currency);
void read_csv(Currency_t**currency);
void select_mode(Currency_t**currency,int choice_num);

void select_mode(Currency_t**currency,int choice_num){
    char mode;
    char direction;
    float amount;
    
    printf("This is the currency you chose\n");
    printf("%-10s%-10.5f\n",currency[choice_num] -> name,currency[choice_num] -> rate);
    printf("\nHere are the modes you can choose\n");
    printf("To convert currency here,trpe 0\n");
    printf("To use this currency to apply on your cash flow,type 1\n");
    printf("To choose another currency,type 2\n");
    printf("\nWhich mode do you want to choose?\n");
    scanf("%c",&mode);
    getchar();
     //error detection
    while(mode != '0' && mode != '1' && mode != '2'){
        printf("Command wrong! please enter 0 , 1 or 2\n");
        scanf("%c",&mode);
        getchar();
    }

    switch (mode){
        case '0':
            while(direction != 'E'){
                system("clear");
                printf("\nMode  0\n");
                printf("This is the currency you chose\n");
                printf("%-10s%-10.5f\n",currency[choice_num] -> name,currency[choice_num] -> rate);
                printf("\nchage from NTD(type F)\nchange to NTD(type T)\nTo exit(type E)\n(F/T/E):");
                scanf("%c", &direction);
                getchar();
                //error detection
                while(direction != 'T' && direction != 'F' && direction != 'E'){
                    printf("Command wrong! please enter T , F or E\n");
                    scanf("%c",&direction);
                    getchar();
                }
                if(direction == 'T'){
                    printf("\nCovert %s to NTD\n",currency[choice_num] -> name);
                    printf("\nEnter the amount of %s:",currency[choice_num] -> name);
                    scanf("%f",&amount);
                    getchar();
                    printf("\n%.2f  %s  =  %.2f  NTD\n\n",amount,currency[choice_num] -> name,(amount * currency[choice_num] -> rate));

                    printf("To continue, type C\nTo exit, type E\n(C/E):");
                    scanf("%c",&direction);
                    getchar();
                    //error detection
                    while(direction != 'C' && direction != 'E' ){
                        printf("Command wrong! please enter C or E\n");
                        scanf("%c",&direction);
                        getchar();
                    }
                    

                }
                else if(direction == 'F'){
                    printf("\nCovert NTD to %s\n",currency[choice_num] -> name);
                    printf("Enter the amount of NTD:");
                    scanf("%f",&amount);
                    getchar();
                    printf("\n%.2f  NTD  =  %.2f  %s\n\n",amount,(amount / currency[choice_num] -> rate),currency[choice_num] -> name);

                    printf("To continue, type C\nTo exit, type E\n(C/E):");
                    scanf("%c",&direction);
                    getchar();
                    //error detection
                    while(direction != 'C' && direction != 'E' ){
                        printf("Command wrong! please enter C or E\n");
                        scanf("%c",&direction);
                        getchar();
                    }
                }
                else if(direction == 'E'){
                    break;
                }

            }
            printf("\n\n --------Exit--------\n\n");
            break;

        case '1':
            //connect to main page
            break;
        
        case '2':
            system("clear");
            read_csv(currency);
            choose_currency(currency);
            break;
    }

}

void choose_currency(Currency_t**currency){
    char user_curr[57];
    
    printf("\nPlease choose the currents you want to convert(Use \'/\' to devide if you want to ):");
    scanf("%s",user_curr);
    
    int counter = 0;
    int choose = 0;
    char confirm;
    char c;
    while(counter !=1 || confirm != '1'){
        counter = 0;
        printf("\nThe current(s) you chose:\n");
        for(int count = 0;count<CURRENCY_NUM;count++){
            if(strstr(user_curr,currency[count] -> name)!= NULL){
                printf("%-10s%-10.5f\n",currency[count] -> name,currency[count] -> rate);
                choose = count;
                counter++;
            }
        }    
            printf("\nIf you find out that currents you chose didn't show up, please check your enters\n");
            printf("The enters should be all in uppercase letters with / between each currency(if needed) and should be the same expreesing as the list shown above\n");
            printf("\nDid you have the correct result shown?(Enter C to comfirm 0 to redo):");
            while (( c = getchar()) != EOF && c != '\n');
            scanf("%c",&confirm);
            getchar();
             //error detection
            while(confirm != 'C' && confirm != '0'){
                printf("Command wrong! please enter C or 0\n");
                scanf("%c",&confirm);
                getchar();
            }

            if(confirm == 'C'){
                
                if(counter != 1){
                    printf("You've totaled entered %d currencies\n", counter);
                    printf("Please choose the \"one\" currency you want to use:");
                    scanf("%s",user_curr);
                    system("clear");
                    read_csv(currency);    
                    continue;
                }
                else{
                    printf("Is this the current you want to use?(type 1 for yes N to redo):");
                    scanf("%c",&confirm);
                    getchar();
                     //error detection
                    while(confirm != '1' && confirm != 'N'){
                        printf("Command wrong! please enter Y or N\n");
                        scanf("%c",&confirm);
                        getchar();
                    }
                    if(confirm=='1'){
                        system("clear");//connect to main page
                        select_mode(currency, choose);
                    }
                    else{
                        system("clear");
                        read_csv(currency);
                        printf("\nPlease choose the currents you want to convert(Use \'/\' to devide if you want to ):");
                        scanf("%s",user_curr);        
                        continue;
                    }
                }
            }
            else{
                system("clear");
                read_csv(currency);
                printf("\nPlease choose the currents you want to convert(Use \'/\' to devide if you want to ):");
                scanf("%s",user_curr);    
                continue;
            }
        
    }
}


void read_csv(Currency_t**currency){
    FILE *cfptr = fopen("ForeignExchangeRate","r");
    if(cfptr == NULL){
        printf("File cannot be opem\n");
    }
    
    char *row ;
    row = (char*) malloc(250);
    
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
    Currency_t** currency;
    currency = (Currency_t**) malloc(CURRENCY_NUM * sizeof(Currency_t*));
    for(int count = 0;count<CURRENCY_NUM;count++){
        currency[count] = (Currency_t*) malloc(sizeof(Currency_t));
    }
    
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
        
        printf("----------File Download Complete----------");
    }
    else{
        system("clear");//back to main page
    }

    //Exchange_Rate CSV file read
    printf("\nHere's the exchange rate for all the currency at %d-%d-%d %d:%d:%d\n",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday,p->tm_hour, p->tm_min, p->tm_sec);
    read_csv(currency);

    //Currency choose by user
    while(1){
        char det;
        choose_currency(currency);
        printf("\nType 1 - To keep using Daily Foreign Exchage Mode \nType 0 - To exit Daily Foreign Exchage Mode\n(0/1):");
        scanf("%c", &det);
        getchar();
         //error detection
        while(det != '0' && det != '1' ){
            printf("Command wrong! please enter 0 or 1\n");
            scanf("%c",&det);
            getchar();
        }
        if(det =='0'){
            printf("\n\n-------Exiting Daily Foreign Exchage Mode-------");
            break;
        }
        else{
            continue;
        }

    }
    
        
    
    
    
    

}