/*
 * fsm.h
 *
 *  Created on: Nov 10, 2023
 *      Author: yshic
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "main.h"
#include "software_timer.h"
#include <stdio.h>
#include "string.h"

#define INIT 		0
#define RECEIVE 	1
#define RST			3
#define OK			4

#define MAX_BUFFER_SIZE 30

extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;
extern uint32_t ADC_value;
extern int command_flag;
extern int status;
extern int cmd;

void clearBuffer();
int compare();
void command_parser_fsm();
void uart_communication_fsm();

#endif /* INC_FSM_H_ */
