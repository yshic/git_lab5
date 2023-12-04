/*
 * fsm.c
 *
 *  Created on: Nov 10, 2023
 *      Author: yshic
 */
#include "fsm.h"

int status = INIT;
int command_flag = 0;
uint8_t temp = 0;
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;
uint8_t buffer[MAX_BUFFER_SIZE];
uint32_t ADC_value = 0;
char str[100];
int cmd = 0;

void clearBuffer(){
	memset(buffer, 0, sizeof(buffer));
	index_buffer = 0;
}
int compare(){
	if(buffer[index_buffer - 4] == 'R' && buffer[index_buffer - 3] == 'S' && buffer[index_buffer - 2] == 'T'){
		return RST;
	}
	else if(buffer[index_buffer - 3] == 'O' && buffer[index_buffer - 2] == 'K'){
		return OK;
	}
	return 0;
}
void command_parser_fsm(){
	switch(status){
	case INIT:
		if(buffer[index_buffer - 1] == '!'){
			status = RECEIVE;
		}
		break;
	case RECEIVE:
		if(buffer[index_buffer - 1] == '#'){
			cmd = compare();
			if(cmd == RST){
				command_flag = 1;
				HAL_ADC_Start(&hadc1);
				ADC_value = HAL_ADC_GetValue(&hadc1);
				HAL_ADC_Stop(&hadc1);
				status = INIT;
				clearBuffer();
				break;
			}
			else if(cmd == OK){
				command_flag = 0;
				status = INIT;
				timer_flag[0] = 1;
				HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_SET);
				clearBuffer();
				break;
			}
		}
		break;
	default:
		break;
	}
}

void uart_communication_fsm(){
	switch(command_flag){
	case 1:
		if(timer_flag[0] == 1){
			HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
			HAL_UART_Transmit(&huart2, "\r\n !ADC=",10,1000);
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "%d#\r\n", ADC_value), 1000);
			setTimer(3000, 0);
		}
		break;
	default:
		break;
	}
}
