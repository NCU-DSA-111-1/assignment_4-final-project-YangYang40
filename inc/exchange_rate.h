#include<stdio.h>
#include<stdlib.h>

#define CURRENCY_NUM 19
typedef struct currency{
    char name[3];
    float rate;
}Currency_t;

void choose_currency(Currency_t**currency);
void read_csv(Currency_t**currency);
void select_mode(Currency_t**currency,int choice_num);
void exchange_rate();