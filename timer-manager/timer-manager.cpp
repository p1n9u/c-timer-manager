#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <time.h>
#include <sys/time.h>

#include <iostream>

#include "timer-manager.h"

using namespace std;

/*
 * Constructors
 */
CTIMERManager::CTIMERManager()
{
}

/*
 * Destructors
 */
CTIMERManager::~CTIMERManager()
{
}

int CTIMERManager::init_tmgr()
{
    minute_change_flag = 0;
    hour_change_flag = 0;
    day_change_flag = 0;
    month_change_flag = 0;
    year_change_flag = 0;

    cur_t = (struct tm *)malloc(sizeof(struct tm));
    if (cur_t == NULL)
        exit(0);

    pre_t = (struct tm *)malloc(sizeof(struct tm));
    if (pre_t == NULL)
        exit(0);

    cur_time = time(NULL);
    pre_time = cur_time;

    this->refresh_localtime(&cur_time, cur_t);
    this->refresh_localtime(&pre_time, pre_t);

    cur_te = (time_element *)malloc(sizeof(time_element));
    if (cur_te == NULL)
        exit(0);

    pre_te = (time_element *)malloc(sizeof(time_element));
    if (pre_te == NULL)
        exit(0);

    this->save_te(cur_te, cur_t);
    this->save_te(pre_te, pre_t);

    return 1;
}

void CTIMERManager::free_tmgr()
{	
    free(cur_te);
    free(pre_te);
    free(cur_t);
    free(pre_t);
}

void CTIMERManager::refresh_localtime(time_t *t_seed, struct tm* t)
{
    localtime_r(t_seed, t);
}

void CTIMERManager::print_time(struct tm* t)
{
    printf("%d-%02d-%02d %02d:%02d:%02d\n", 
            1900+t->tm_year, t->tm_mon+1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);
}

void CTIMERManager::save_te(time_element *te, struct tm* t)
{
    te->year = 1900 + (t->tm_year);
    te->month = (t->tm_mon) + 1;
    te->day = t->tm_mday;
    te->hour = t->tm_hour;
    te->minute = t->tm_min;
    te->second = t->tm_sec;
}

void CTIMERManager::print_te(time_element *te)
{
    printf("====================================\n");
    printf("[te->member]\n");
    printf("    year  : %d\n", te->year);
    printf("    month : %d\n", te->month);
    printf("    day   : %d\n", te->day);
    printf("    hour  : %d\n", te->hour);
    printf("    min   : %d\n", te->minute);
    printf("    sec   : %d\n", te->second);
    printf("====================================\n");
}

int CTIMERManager::compare_te_minute(time_element *cur_te, time_element *pre_te)
{
    return (cur_te->minute != pre_te->minute);
}

int CTIMERManager::compare_te_hour(time_element *cur_te, time_element *pre_te)
{
    return (cur_te->hour != pre_te->hour);
}

int CTIMERManager::compare_te_day(time_element *cur_te, time_element *pre_te)
{
    return (cur_te->day != pre_te->day);
}

int CTIMERManager::compare_te_month(time_element *cur_te, time_element *pre_te)
{
    return (cur_te->month != pre_te->month);
}

int CTIMERManager::compare_te_year(time_element *cur_te, time_element *pre_te)
{
    return (cur_te->year != pre_te->year);
}

int CTIMERManager::check_by_interval(long base)
{
    long interval = (this->cur_time) - (this->pre_time);
    return (interval > base);
}