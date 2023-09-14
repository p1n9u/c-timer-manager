#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <time.h>
#include <sys/time.h>

#include <iostream>

typedef struct time_element {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} time_element;

class CTIMERManager {	
public:
	/*
	 * Constructors
	 */
	CTIMERManager();

	/*
	 * Destructors
	 */
	~CTIMERManager();

	/*
	 * Interfaces
	 */
    int init_tmgr();
    void free_tmgr();
    void refresh_timeseed(time_t *t_seed, time_t *seconds);
    void refresh_localtime(time_t *t_seed, struct tm* t);
    void print_time(struct tm* t);
    void save_te(time_element *te, struct tm* t);
    void print_te(time_element *te);
    int compare_te_minute(time_element *cur_te, time_element *pre_te);
    int compare_te_hour(time_element *cur_te, time_element *pre_te);
    int compare_te_day(time_element *cur_te, time_element *pre_te);
    int compare_te_month(time_element *cur_te, time_element *pre_te);
    int compare_te_year(time_element *cur_te, time_element *pre_te);
    int check_by_interval(long base);

protected:
	/*
	 * Member Functions
	 */

public:
	/*
	 * Member Attributes
	 */
    int minute_change_flag;
    int hour_change_flag;
    int day_change_flag;
    int month_change_flag;
    int year_change_flag;
    struct tm *cur_t;
    struct tm *pre_t;
    time_element *cur_te;
    time_element *pre_te;
    time_t cur_time;
    time_t pre_time;
};