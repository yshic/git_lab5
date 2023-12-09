#ifndef APP_SCHEDULER_H_
#define APP_SCHEDULER_H_

#include "stdint.h"


#define SCH_MAX_TASKS 			10

void SCH_Init(void);
void SCH_Update(void);
uint32_t SCH_Add_Task(void (*p_function)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Dispatch_Tasks(void);
uint8_t SCH_Delete_Task(uint32_t TASK_ID);

#endif /* APP_SCHEDULER_H_ */
