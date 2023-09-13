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
    struct timespec rts;
    timespec_get(&rts, TIME_UTC);
    struct tm *t;
    t = localtime(&rts.tv_sec);
    while (true) {
        print_time(t);
        timespec_get(&rts, TIME_UTC);
        t = localtime(&rts.tv_sec);
        sleep(1);
        system("clear");
    }

    return 0;
}