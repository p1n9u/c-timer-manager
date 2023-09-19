#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include <time.h>
#include <sys/time.h>

#include <iostream>

#include "./timer-manager/timer-manager.h"

using namespace std;
CTIMERManager timer_mgr = CTIMERManager();

static void min_status(char *buf)
{
    static int i = 0;
    i++;
    sprintf(buf, "min changed %d times...\n", i);
}

static void hour_status(char *buf)
{
    static int i = 0;
    i++;
    sprintf(buf, "hour changed %d times...\n", i);
}

int main(int argc, char *argv[])
{
    int timer_res;
    char min_buf[1024];
    char hour_buf[1024];
    memset(min_buf, '\0', sizeof(char) * 1024);
    memset(hour_buf, '\0', sizeof(char) * 1024);

    timer_res = timer_mgr.init_tmgr();

    system("clear");
    while (true) {
        timer_mgr.refresh_timeseed(&(timer_mgr.cur_time), NULL);
        timer_mgr.refresh_localtime(&(timer_mgr.cur_time), timer_mgr.cur_t);
        timer_mgr.save_te(timer_mgr.cur_te, timer_mgr.cur_t);

        printf("========================================\n");
        printf("[Current Time] : ");
        timer_mgr.print_time(timer_mgr.cur_te);
        printf("========================================\n");
        printf("[Previous Time]: ");
        timer_mgr.print_time(timer_mgr.pre_te);
        printf("========================================\n");
        printf("%s", min_buf);
        printf("%s", hour_buf);
        printf("========================================\n");

        timer_res = timer_mgr.check_by_interval(10);
        if (timer_res) {
            timer_mgr.pre_time = timer_mgr.cur_time;
            timer_res = timer_mgr.compare_te_minute(timer_mgr.cur_te, timer_mgr.pre_te);
            if (timer_res) {
                timer_mgr.refresh_flag = 1;
                timer_mgr.minute_change_flag = 1;
            }
            timer_res = timer_mgr.compare_te_minute(timer_mgr.cur_te, timer_mgr.pre_te);
            if (timer_res) {
                timer_mgr.refresh_flag = 1;
                timer_mgr.minute_change_flag = 1;
            }
        }

        if (timer_mgr.minute_change_flag)
            min_status(min_buf);

        if (timer_mgr.hour_change_flag)
            hour_status(hour_buf);

        if (timer_mgr.refresh_flag) {
            timer_mgr.refresh_localtime(&(timer_mgr.pre_time), timer_mgr.pre_t);
            timer_mgr.save_te(timer_mgr.pre_te, timer_mgr.pre_t);
            timer_mgr.refresh_flag = 0;
            timer_mgr.minute_change_flag = 0;
            timer_mgr.hour_change_flag = 0;
        }

        sleep(1);
        system("clear");
    }

    timer_mgr.free_tmgr();
    return 0;
}