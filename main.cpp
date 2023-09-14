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

int main(int argc, char *argv[])
{
    int timer_res;

    timer_res = timer_mgr.init_tmgr();

    system("clear");
    while (true) {
        timer_mgr.cur_time = time(NULL);
        timer_mgr.refresh_localtime(&(timer_mgr.cur_time), timer_mgr.cur_t);
        timer_mgr.save_te(timer_mgr.cur_te, timer_mgr.cur_t);

        printf("====================================\n");
        printf("[Current Time]: ");
        timer_mgr.print_time(timer_mgr.cur_t);
        timer_mgr.print_te(timer_mgr.cur_te);
        printf("[Previous Time]: ");
        timer_mgr.print_time(timer_mgr.pre_t);
        timer_mgr.print_te(timer_mgr.pre_te);

        timer_res = timer_mgr.check_by_interval(10);
        if (timer_res) {
            timer_mgr.pre_time = timer_mgr.cur_time;
            timer_res = timer_mgr.compare_te_minute(timer_mgr.cur_te, timer_mgr.pre_te);
            if (timer_res)
                timer_mgr.minute_change_flag = 1;
        }

        if (timer_mgr.minute_change_flag) {
            timer_mgr.refresh_localtime(&(timer_mgr.pre_time), timer_mgr.pre_t);
            timer_mgr.save_te(timer_mgr.pre_te, timer_mgr.pre_t);
            timer_mgr.minute_change_flag = 0;
        }

        sleep(1);
        system("clear");
    }

    timer_mgr.free_tmgr();
    return 0;
}