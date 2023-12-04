#include "software_timer.h"

int timer_counter[MAX_TIMERS] = {0};
int timer_flag[MAX_TIMERS] = {0};

void setTimer(int duration, int id){
	timer_counter[id] = duration/TICK;
	timer_flag[id] = 0;
}
void timerRun(){
	for(int i = 0; i < MAX_TIMERS; i++){
		if(timer_counter[i] > 0){
			timer_counter[i]--;
			if(timer_counter[i] <= 0){
				timer_flag[i] = 1;
			}
		}
	}
}
