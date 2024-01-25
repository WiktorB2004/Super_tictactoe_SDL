#pragma once
#include <time.h>

typedef long long Timer;

int seconds_left(Timer timer);
void set_timer(Timer *timer, int seconds);

void engine();