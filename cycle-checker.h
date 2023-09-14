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