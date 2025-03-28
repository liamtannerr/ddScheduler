#include "../inc/DDS.h"
#include "../inc/linkedList.h"  // Include the linked list header to define taskListNode
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void checkOverdue(struct taskListNode** active, struct taskListNode** overdue) {
    if (*active == NULL)
        return;

    int position = 0;
    struct taskListNode* temp = *active;
    while (temp != NULL) {  // Go through the entire list
        int current_time = xTaskGetTickCount();  // Get the current time from FreeRTOS
        if (current_time > temp->deadline) {  // Task is overdue
            insertAtEnd(overdue, temp);  // Pass pointer directly, no need for &temp
            deleteAtPosition(active, position);  // Correct function name
        }
        position++;
        temp = temp->next;  // Move to the next node
    }
}



