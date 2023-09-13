#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <time.h>
#include <sys/time.h>

#include <iostream>

static void print_time(struct tm* t)
{
    printf("%d-%02d-%02d %02d:%02d:%02d\n", 
            1900+t->tm_year, t->tm_mon+1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);
}

int main(void)
{
    struct tm cur_t;
    struct tm pre_t;

    time_t cur_time = time(NULL);
	time_t pre_time = 0;

    localtime_r(&cur_time, &cur_t);
    while (true) {
        printf("cur_time : ");
        print_time(&cur_t);
        printf("pre_time : ");
        print_time(&pre_t);

        cur_time = time(NULL);
        localtime_r(&cur_time, &cur_t);
        if ( cur_time - pre_time > 10 ) {
            printf("updating pre time...\n");
            pre_time = cur_time;
            localtime_r(&pre_time, &pre_t);
        }

        sleep(1);
        system("clear");
    }

    return 0;
}