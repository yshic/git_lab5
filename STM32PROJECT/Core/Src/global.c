#include "global.h"
#include "main.h"
#include "software_timer.h"

void timerBlinkInit(){
	setTimer(10, 1);
}

void setLED(){
	HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
}

void ledBlinky(){
	if(timer_flag[1] == 1){
		HAL_GPIO_TogglePin(LED_RED_BLINKY_GPIO_Port, LED_RED_BLINKY_Pin);
		setTimer(2000, 1);
	}
}

