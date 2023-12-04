#include "software_timer.h"
#define TICK 10

int timer_counter[16] = {0};
int timer_flag[16] = {0};

void setTimer(int duration, int id){
	timer_counter[id] = duration/TICK;
	timer_flag[id] = 0;
}
void timerRun(int id){
	if(timer_counter[id] > 0){
		timer_counter[id]--;
		if(timer_counter[id] <= 0){
			timer_flag[id] = 1;
		}
	}
}
