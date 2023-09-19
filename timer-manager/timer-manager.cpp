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
    refresh_flag = 0;
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

    cur_te->day_of_week_string = (char *)malloc(sizeof(char) * 4);
    pre_te->day_of_week_string = (char *)malloc(sizeof(char) * 4);
    memset(cur_te->day_of_week_string, '\0', sizeof(char) * 4);
    memset(pre_te->day_of_week_string, '\0', sizeof(char) * 4);

    this->save_te(cur_te, cur_t);
    this->save_te(pre_te, pre_t);

    return 1;
}

void CTIMERManager::free_tmgr()
{	
    free(cur_te->day_of_week_string);
    free(pre_te->day_of_week_string);
    free(cur_te);
    free(pre_te);
    free(cur_t);
    free(pre_t);
}

void CTIMERManager::refresh_timeseed(time_t *t_seed, time_t *seconds)
{
    *t_seed = time(seconds);
}

void CTIMERManager::refresh_localtime(time_t *t_seed, struct tm* t)
{
    localtime_r(t_seed, t);
}

void CTIMERManager::print_time(time_element *te)
{
    printf("%d-%02d-%02d %s %02d:%02d:%02d\n",
            te->year, te->month, te->day, te->day_of_week_string,
            te->hour, te->minute, te->second);
}

void CTIMERManager::convert_day_of_week(char *day_of_week_string, int day_of_week)
{
    switch (day_of_week) {
    case 0:
        strncpy(day_of_week_string, "SUN", 3);
        break;
    case 1:
        strncpy(day_of_week_string, "MON", 3);
        break;
    case 2:
        strncpy(day_of_week_string, "TUE", 3);
        break;
    case 3:
        strncpy(day_of_week_string, "WED", 3);
        break;
    case 4:
        strncpy(day_of_week_string, "THU", 3);
        break;
    case 5:
        strncpy(day_of_week_string, "FRI", 3);
        break;
    case 6:
        strncpy(day_of_week_string, "SAT", 3);
        break;
    }
    return;
}

/**
 *
 *

 */
void CTIMERManager::save_te(time_element *te, struct tm* t)
{
    te->year = 1900 + (t->tm_year);
    te->month = (t->tm_mon) + 1;
    te->day = t->tm_mday;
    te->hour = t->tm_hour;
    te->minute = t->tm_min;
    te->second = t->tm_sec;
    te->day_of_week = t->tm_wday;
    this->convert_day_of_week(te->day_of_week_string, t->tm_wday);
}

void CTIMERManager::print_te(time_element *te)
{
    printf("====================================\n");
    printf("[te->member]\n");
    printf("    year  : %4d\n", te->year);
    printf("    month : %02d\n", te->month);
    printf("    day   : %02d\n", te->day);
    printf("    hour  : %02d\n", te->hour);
    printf("    min   : %02d\n", te->minute);
    printf("    sec   : %02d\n", te->second);
    printf("    dow   : %s\n", te->day_of_week_string);
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