#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include"file_download.h"


void filedownload(){
    //char filename[30];

    // time_t timep;
    // struct tm *p;
    // time(&timep);
    // p = gmtime(&timep);//get localtime


    //snprintf(filename,30,"%d/%d/%d ForeignExchangeRate",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday);
    //printf("%s",filename);
    
    system("wget 'https://rate.bot.com.tw/xrt/flcsv/0/day' -O  'ForeignExchangeRate' -nv");


}