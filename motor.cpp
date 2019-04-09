/*
 * motor.cpp
 *
 *  Created on: 5 Apr 2019
 *      Author: Vincent
 */

#include <avr/io.h>
#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>
#include "constants.h"

QueueHandle_t xQueueLeft = xQueueCreate(10, sizeof(int));
QueueHandle_t xQueueRight = xQueueCreate(10, sizeof(int));

void left(void *p)
{
	int dc = 0;
	bool isForward = true;
	for (;;) {
		if (xQueueReceive(xQueueLeft, &dc, (TickType_t) 0) == pdTRUE) {
			isForward = dc > 0;
			dc = abs(dc);
		}
		if (isForward) {
//			digitalWrite(LEFT_REVERSE, LOW);
//			digitalWrite(LEFT_FORWARD, HIGH);
//			vTaskDelay(dc);
//			digitalWrite(LEFT_FORWARD, LOW);
//			vTaskDelay(40 - dc);
			digitalWrite(LEFT_REVERSE, LOW);
			analogWrite(LEFT_FORWARD, dc);
			vTaskDelay(40);
		}
		else {
//			digitalWrite(LEFT_FORWARD, LOW);
//			digitalWrite(LEFT_REVERSE, HIGH);
//			vTaskDelay(dc);
//			digitalWrite(LEFT_REVERSE, LOW);
//			vTaskDelay(40 - dc);
			digitalWrite(LEFT_FORWARD, LOW);
			analogWrite(LEFT_REVERSE, dc);
			vTaskDelay(40);
		}
	}
}

void right(void *p)
{
	int dc = 0;
	bool isForward = true;
	for (;;) {
		if (xQueueReceive(xQueueRight, &dc, (TickType_t) 0) == pdTRUE) {
			isForward = dc > 0;
			dc = abs(dc);
		}
		if (isForward) {
//			digitalWrite(RIGHT_REVERSE, LOW);
//			digitalWrite(RIGHT_FORWARD, HIGH);
//			vTaskDelay(dc);
//			digitalWrite(RIGHT_FORWARD, LOW);
//			vTaskDelay(40 - dc);
			digitalWrite(RIGHT_REVERSE, LOW);
			analogWrite(RIGHT_FORWARD, dc);
			vTaskDelay(40);
		}
		else {
//			digitalWrite(RIGHT_FORWARD, LOW);
//			digitalWrite(RIGHT_REVERSE, HIGH);
//			vTaskDelay(dc);
//			digitalWrite(RIGHT_REVERSE, LOW);
//			vTaskDelay(40 - dc);
			digitalWrite(RIGHT_FORWARD, LOW);
			analogWrite(RIGHT_REVERSE, dc);
			vTaskDelay(40);
		}
	}
}


