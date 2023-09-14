#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <time.h>
#include <sys/time.h>

#include <iostream>

#include "cycle-checker.h"

static void print_time(struct tm* t)
{
    printf("%d-%02d-%02d %02d:%02d:%02d\n", 
            1900+t->tm_year, t->tm_mon+1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);
}

static void save_te(time_element *te, struct tm* t)
{
    te->year = 1900 + (t->tm_year);
    te->month = (t->tm_mon) + 1;
    te->day = t->tm_mday;
    te->hour = t->tm_hour;
    te->minute = t->tm_min;
    te->second = t->tm_sec;
}

static void print_te(time_element *te)
{
    printf("=================================\n");
    printf("[te->member]\n");
    printf("    year  : %d\n", te->year);
    printf("    month : %d\n", te->month);
    printf("    day   : %d\n", te->day);
    printf("    hour  : %d\n", te->hour);
    printf("    min   : %d\n", te->minute);
    printf("    sec   : %d\n", te->second);
    printf("=================================\n");
}

static int compare_te_min(time_element *cur_te, time_element *pre_te)
{
    return (cur_te->minute != pre_te->minute);
}

int main(void)
{
    int change_flag = 0;

    struct tm *cur_t = (struct tm *)malloc(sizeof(struct tm));
    struct tm *pre_t = (struct tm *)malloc(sizeof(struct tm));
    
    time_t cur_time = time(NULL);
    time_t pre_time = cur_time;

    localtime_r(&cur_time, cur_t);
    localtime_r(&pre_time, pre_t);

    time_element *cur_te = (time_element *)malloc(sizeof(time_element));
    time_element *pre_te = (time_element *)malloc(sizeof(time_element));

    save_te(cur_te, cur_t);
    save_te(pre_te, pre_t);
    
    system("clear");
    while (true) {
        cur_time = time(NULL);
        localtime_r(&cur_time, cur_t);
        save_te(cur_te, cur_t);

        print_te(cur_te);
        print_te(pre_te);

        printf("cur_time : ");
        print_time(cur_t);
        printf("pre_time : ");
        print_time(pre_t);

        printf("=================================\n");

        if ( cur_time - pre_time > 10 ) {
            pre_time = cur_time;
            if (compare_te_min(cur_te, pre_te)) {
                printf("change flag!!!\n");
                change_flag = 1;
            }
        }

        if (change_flag) {
            localtime_r(&pre_time, pre_t);
            save_te(pre_te, pre_t);
            change_flag = 0;
        }

        sleep(1);
        system("clear");
    }

    free(cur_te);
    free(pre_te);
    free(cur_t);
    free(pre_t);

    return 0;
}