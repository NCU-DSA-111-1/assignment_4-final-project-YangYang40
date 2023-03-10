#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>
#include"store.h"

#define NAMELENGTH 25

// typedef struct elements{
//     char giver[NAMELENGTH];
//     char getter[NAMELENGTH];
//     float money;
// }Elements_t;

// typedef struct data{
//     char people[NAMELENGTH];
//     float action;
//     struct data* previous;
//     struct data* next;
// }Data_t;

// typedef struct data_queue{
//     Data_t* front;
//     Data_t* rear;
// }Dataqueue_t;

// typedef struct userlist{
//     char username[NAMELENGTH];
//     Dataqueue_t* userdata;
//     struct userlist* previous;
//     struct userlist* next;
// }Userlist_t;

// typedef struct user_queue{
//     Userlist_t* front;
//     Userlist_t* rear;
// }Userqueue_t;

// Dataqueue_t* init_dataqueue();
// Userqueue_t* init_userqueue();
// void user_insert( Userqueue_t *const que, char username[NAMELENGTH]);
// void data_insert( Dataqueue_t *const que, char person[NAMELENGTH], float action);
// int check_name(Userqueue_t* users, char name[NAMELENGTH]);
// void remove_one_data(Dataqueue_t* datas);
// void delete_data(Dataqueue_t* datas ,Data_t* target);
// void search_and_delete(Userqueue_t* users);
// void user_store(Elements_t** info);

Dataqueue_t* init_dataqueue(){
    Dataqueue_t* que = (Dataqueue_t*)malloc(sizeof(Dataqueue_t));
    que -> front = NULL;
    que -> rear = NULL;
    return que;
}

Userqueue_t* init_userqueue(){
    Userqueue_t* que = (Userqueue_t*)malloc(sizeof(Userqueue_t));
    que -> front = NULL;
    que -> rear = NULL;

    return que;
}


void user_insert( Userqueue_t *const que, char username[NAMELENGTH]){

    Userlist_t* node = (Userlist_t*)malloc(sizeof(Userlist_t));
    //copy the name and init the datasqueue 
    strncpy((node -> username),username,NAMELENGTH);
    node -> userdata = init_dataqueue();
    node -> next = NULL;

    if(que->rear == NULL){
        que->front = node;
    }
    else{
        que -> rear -> next = node;
        node -> previous = que -> rear;
    }
    que -> rear = node;

    
    return;
}


void data_insert( Dataqueue_t *const que, char person[NAMELENGTH], float action){

    Data_t* node = (Data_t*)malloc(sizeof(Data_t));
    //copy the name and init the datastack
    strncpy((node -> people),person,NAMELENGTH);
    node -> action = action;
    node -> next = NULL;
    
    if(que->rear == NULL){
        que->front = node;
    }
    else{
        que -> rear -> next = node;
        node -> previous = que -> rear;
    }
    que -> rear = node;

    return;
}

int check_name(Userqueue_t* users, char name[NAMELENGTH]){
    Userlist_t* tmp = users->front;
    int count;
    for(count = 0; tmp!=NULL; count++){
        if(strstr(tmp->username,name) != NULL){
            return (count);
        }
        else{
            tmp = tmp->next;
        }
    }

    return -1;
}

void remove_one_data(Dataqueue_t* datas){
    Data_t* tmp;
    if(datas -> front  == NULL){
        printf("No data!\n");
    }
    tmp = datas -> front;
    datas -> front = datas -> front -> next;
    if(datas -> front == NULL){
        datas -> rear = NULL;
    }
    free (tmp);
}

void delete_data(Dataqueue_t* datas ,Data_t* target){
    Data_t* nextptr;
    if(target == NULL){
        printf("No data remain\n");
    }
    else if(target->next == NULL){
        remove_one_data(datas);
    }
    nextptr = target -> next;
    target -> next = nextptr -> next;
    free(nextptr);
}

void search_and_delete(Userqueue_t* users){
    int result;
    int loop = 2;
    int count = 1;
    int deletenum = 0;
    char name[NAMELENGTH];
    Data_t *tmpdata;
    Userlist_t *usertmp;
   
    
    
    
    printf("Please enter your user name:");
    scanf("%s",name);
    getchar();
    result = check_name(users,name);
    // printf("%d",result);
    while(loop!=0){
        count = 1;
        if(result != -1){
            usertmp = users ->front;
            //shift
            for(int i=0;i<result;i++){
                usertmp=usertmp->next;
            }
            //set tmpdata at front
            tmpdata = usertmp -> userdata -> front;
            //empty - nodata
            if(tmpdata == NULL){
                printf("no data");
            }
            //print
            while(tmpdata!=NULL){
                printf("%d.  ",count);
                if(tmpdata->action > 0){
                    //you are a getter
                    printf("%s shold give you %f dollar\n\n",tmpdata->people,tmpdata->action);
                }
                else{
                    //you are a giver
                    printf("You shold give %s %f dollars\n\n",tmpdata->people,(-1)*(tmpdata->action));
                }
                tmpdata = tmpdata->next;
                count++;
            }
            //continue?
            printf("Search for another user? type 1 for yes, 0 to continue\n(1/0):");
            scanf("%d",&loop);
            if(loop==1){
                printf("Please enter your user name:");
                scanf("%s",name);
                getchar();
                result = check_name(users,name);
            }
            
        }
        else{
            printf("User not found! try again!\n");
            printf("Please enter your user name:");
            scanf("%s",name);
            getchar();
            result = check_name(users,name);
        }
    }
    //delete mode
    //reset tmpdata at front
    tmpdata = usertmp -> userdata -> front;
    printf("Do you want to delete any of the history?\n");
    printf("If yes type the number of the history\nIf no type 0\n:");
    scanf("%d",&deletenum);

    while(deletenum != 0){
        //TODO confirm system
        //shift
        for(int i=0;i<deletenum-1;i++){
            tmpdata = tmpdata -> next;
        }
        //delete
        delete_data(usertmp -> userdata,tmpdata);
        printf("To delete another history, type the number of the history\n To stop type 0\n:");
        scanf("%d",&deletenum);
        

    
    }
}

void user_store(Elements_t** info,int num){
    // store the datas to the linklist
    
    Userqueue_t* users = init_userqueue();
   
    int shift;
   
    
    for(int count = 0; count< num;count++){
        if(users -> front == NULL){
            //giver -- user who shold pay money to getter (action (-money))
            user_insert(users, info[count]->giver);
            data_insert(users->front->userdata, info[count]->getter, ((-1)*info[count]->money));
            //getter -- user who should get money from giver(action (money))
            user_insert(users, info[count]->getter);
            data_insert(users->rear->userdata, info[count]->giver, info[count]->money);
            
        }
        else{
            //check if giver's name is on the list
            Userlist_t* tmp = users->front;
            shift = check_name(users,info[count]->giver);
            
            //printf("%d\n",shift);
            if(shift !=-1){
                //shift
                for(int i=0;i<shift;i++){
                    tmp=tmp->next;
                }
                data_insert(tmp -> userdata,info[count] ->getter, ((-1)*info[count]->money)); 
            }
            else{
                user_insert(users, info[count]->giver);
                data_insert(users->rear->userdata, info[count]->getter, ((-1)*info[count]->money));
            }

            //check if getter's name is on the list
            tmp = users->front;
            //printf("%s\n",info[count] -> giver);
            //printf("%s\n",info[count] -> getter);
            shift = check_name(users,info[count]->getter);
            //printf("getter%d\n",shift);
            if(shift !=-1){
                //shift
                for(int i=0;i<shift;i++){
                    tmp=tmp->next;
                }
                data_insert(tmp -> userdata,info[count] ->giver, info[count]->money); 
            }
            else{
                user_insert(users, info[count]->getter);
                data_insert(users->rear->userdata, info[count]->getter, info[count]->money);
            }
        }
    }
    
    search_and_delete(users);

    


    
}