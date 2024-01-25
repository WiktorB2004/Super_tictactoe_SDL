#include "../include/utils/timer.h"

Timer current_time()
{
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    return current_time.tv_sec;
}

int seconds_left(Timer timer)
{
    Timer left = (timer - current_time());

    return left < 0 ? 0 : left;
}

void set_timer(Timer *timer, int seconds)
{
    *timer = current_time() + seconds;
}