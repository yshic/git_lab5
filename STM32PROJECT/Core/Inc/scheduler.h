/*
 * scheduler.h
 *
 *  Created on: Nov 29, 2023
 *      Author: yshic
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "stdint.h"

#define SCH_MAX_TASKS 	10
#define	NO_TASK_ID		0

void SCH_Init(void);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
uint8_t SCH_Delete_Task(uint32_t TASK_ID);
uint32_t SCH_Add_Task(void (*p_function)(), uint32_t DELAY, uint32_t PERIOD);

static uint32_t Get_New_Task_ID(void);

#endif /* INC_SCHEDULER_H_ */
