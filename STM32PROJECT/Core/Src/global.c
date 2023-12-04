#include "global.h"
#include "main.h"
#include "software_timer.h"

void setLED(){
	HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
}
