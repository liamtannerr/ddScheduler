#include "../inc/DDS.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/task.h"
#include "../FreeRTOS_Source/include/queue.h"

#include "../inc/DDS.h"
#include "../inc/linkedList.h"
#include "../inc/mergeSort.h"

void checkOverdue(struct taskListNode** active, struct taskListNode** overdue){
    if (*head == NULL)
        return;
    int position = 0;
    struct taskListNode* temp = *active;
    while (temp->next != NULL) {
    	int current_time = xTaskGetTickCount();
    	if(current_time > temp->deadline){
            insertAtEnd(overdue, &temp);
            deletefromPosition(active, position);
        }
    	position++;
        temp = temp->next;
    }
    return;
}
