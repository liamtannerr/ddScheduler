/*
 * userDefined.c
 *
 *  Created on: Mar 27, 2025
 *      Author: liamtanner
 */

#include "../inc/userDefined.h"
#include "../inc/linkedList.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/queue.h"
#include "../FreeRTOS_Source/include/semphr.h"
#include "../FreeRTOS_Source/include/task.h"
#include "../FreeRTOS_Source/include/timers.h"
#include "../inc/main.h"

extern xQueueHandle User_Defined_Queue;
extern TaskHandle_t DDS;

void User_Defined_Task(void *pvParameters) {


	printf("WE ARE IN USER DEFINED TASK\n");
    struct taskListNode* currentTask;

    while (1) {
        // Wait for task pointer from DDS
        if ( xQueueReceive(User_Defined_Queue,&currentTask,1000)) {
            printf("User Defined Task: Executing task %d\n", currentTask->task_id);

            TickType_t start = xTaskGetTickCount();
            TickType_t now;
            TickType_t duration = currentTask->execution_time / portTICK_PERIOD_MS;

            while ((now = xTaskGetTickCount()) - start < duration) {
                // Simulate execution
            }

            int result = 1; // 1 for success
            xQueueSend(User_Defined_Queue, &result, portMAX_DELAY);
            vTaskResume(DDS);
            printf("User Defined Task: Completed task %d\n", currentTask->task_id);
        }
    }
}
