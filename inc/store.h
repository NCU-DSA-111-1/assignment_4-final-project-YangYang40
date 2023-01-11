#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

#define NAMELENGTH 25

typedef struct elements{
    char giver[NAMELENGTH];
    char getter[NAMELENGTH];
    float money;
}Elements_t;

typedef struct data{
    char people[NAMELENGTH];
    float action;
    struct data* previous;
    struct data* next;
}Data_t;

typedef struct data_queue{
    Data_t* front;
    Data_t* rear;
}Dataqueue_t;

typedef struct userlist{
    char username[NAMELENGTH];
    Dataqueue_t* userdata;
    struct userlist* previous;
    struct userlist* next;
}Userlist_t;

typedef struct user_queue{
    Userlist_t* front;
    Userlist_t* rear;
}Userqueue_t;

Dataqueue_t* init_dataqueue();
Userqueue_t* init_userqueue();
void user_insert( Userqueue_t *const que, char username[NAMELENGTH]);
void data_insert( Dataqueue_t *const que, char person[NAMELENGTH], float action);
int check_name(Userqueue_t* users, char name[NAMELENGTH]);
void remove_one_data(Dataqueue_t* datas);
void delete_data(Dataqueue_t* datas ,Data_t* target);
void search_and_delete(Userqueue_t* users);
void user_store(Elements_t** info,int num);