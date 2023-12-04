#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer_flag[16];

void setTimer(int duration, int id);

void timerRun(int id);

#endif /* INC_SOFTWARE_TIMER_H_ */
