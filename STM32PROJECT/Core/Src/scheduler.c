#include "scheduler.h"
#include "main.h"

typedef struct {
	void ( * pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} sTask;

// The array of tasks
static sTask SCH_tasks_G[SCH_MAX_TASKS];

int tasks_num = 0; //number of current tasks

void SCH_Init(void){
	for(uint32_t i = 0; i < SCH_MAX_TASKS; i++){
		SCH_tasks_G[i].pTask = 0x0000;
		SCH_tasks_G[i].Delay = 0;
		SCH_tasks_G[i].Period = 0;
		SCH_tasks_G[i].RunMe = 0;
		SCH_tasks_G[i].TaskID = i;
	}
}

void SCH_Update(void){
	// Check if there is a task at this location
	if (SCH_tasks_G[0].pTask && SCH_tasks_G[0].RunMe == 0) {
		if(SCH_tasks_G[0].Delay > 0){
			SCH_tasks_G[0].Delay = SCH_tasks_G[0].Delay - 1;
		}
		if (SCH_tasks_G[0].Delay == 0) {
			SCH_tasks_G[0].RunMe = 1;
		}
	}
}

uint32_t SCH_Add_Task(void (* pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	uint32_t sumDelay = 0;
	uint32_t newDelay = 0;

	for(uint32_t i = 0; i < SCH_MAX_TASKS; i++){
		if(SCH_tasks_G[i].pTask == 0x0000){
			SCH_tasks_G[i].pTask = pFunction;
			SCH_tasks_G[i].Delay = DELAY - sumDelay;
			SCH_tasks_G[i].Period = PERIOD;
			SCH_tasks_G[i].TaskID = i;
			SCH_tasks_G[i].RunMe = 0;
			if(DELAY == 0){
				SCH_tasks_G[i].RunMe = 1;
			}
			tasks_num++;
			return SCH_tasks_G[i].TaskID;
		}
		else{
			if(DELAY < sumDelay + SCH_tasks_G[i].Delay){
				newDelay = DELAY - sumDelay;
				SCH_tasks_G[i].Delay = SCH_tasks_G[i].Delay - newDelay;
				for(uint32_t j = tasks_num; j > i; j--){
					SCH_tasks_G[j].pTask = SCH_tasks_G[j-1].pTask;
					SCH_tasks_G[j].Delay = SCH_tasks_G[j-1].Delay;
					SCH_tasks_G[j].Period = SCH_tasks_G[j-1].Period;
					SCH_tasks_G[j].RunMe = SCH_tasks_G[j-1].RunMe;
					SCH_tasks_G[j].TaskID = SCH_tasks_G[j-1].TaskID + 1;
				}
	            SCH_tasks_G[i].pTask = pFunction;
	            SCH_tasks_G[i].Delay = DELAY - sumDelay;
	            SCH_tasks_G[i].Period = PERIOD;
	            SCH_tasks_G[i].RunMe = 0;
	            if(DELAY == 0){
	            	SCH_tasks_G[i].RunMe = 1;
	            }
	            SCH_tasks_G[i].TaskID = i;
	            tasks_num++;
	            return SCH_tasks_G[i].TaskID;
			}
			else{
				sumDelay = sumDelay + SCH_tasks_G[i].Delay;
			}
		}
	}
	return -1;
}


uint8_t SCH_Delete_Task(uint32_t taskID){
	uint8_t Return_code  = 0;
	uint8_t j;
	if(taskID >= 0 && taskID < SCH_MAX_TASKS){
		Return_code = 1;
		for(uint32_t i = taskID; i < tasks_num; i++){ //shift the tasks at the deleted task backward
			SCH_tasks_G[i].pTask = SCH_tasks_G[i+1].pTask;
			SCH_tasks_G[i].Delay = SCH_tasks_G[i+1].Delay;
			SCH_tasks_G[i].Period = SCH_tasks_G[i+1].Period;
			SCH_tasks_G[i].RunMe = SCH_tasks_G[i+1].RunMe;
			SCH_tasks_G[i].TaskID = SCH_tasks_G[i+1].TaskID - 1;
		}
		SCH_tasks_G[tasks_num - 1].pTask = 0;
		SCH_tasks_G[tasks_num - 1].Delay = 0;
		SCH_tasks_G[tasks_num - 1].Period = 0;
		SCH_tasks_G[tasks_num - 1].RunMe = 0;
		SCH_tasks_G[tasks_num - 1].TaskID = 0;
		tasks_num--;
	}
	return Return_code; // return status
}

void SCH_Dispatch_Tasks(void){
	if(SCH_tasks_G[0].RunMe > 0) {
		(*SCH_tasks_G[0].pTask)(); // Run the task
		SCH_tasks_G[0].RunMe = 0; // Reset / reduce RunMe flag
		sTask temtask = SCH_tasks_G[0];
		SCH_Delete_Task(temtask.TaskID);
		if (temtask.Period != 0) {
			SCH_Add_Task(temtask.pTask, temtask.Period, temtask.Period);
		}
	}
	// Enter low-power mode (Sleep mode). The MCU will wake up on the next interrupt
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}
