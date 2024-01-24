#pragma once
#include "time.h"

typedef long long Timer;

Timer current_time_ms();
int seconds_left(Timer timer);
void set_timer(Timer *timer, int seconds);