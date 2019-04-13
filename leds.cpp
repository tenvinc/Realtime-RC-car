/*
 * leds.cpp
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

SemaphoreHandle_t xSemaphoreGreen = xSemaphoreCreateBinary();
SemaphoreHandle_t xSemaphoreRed = xSemaphoreCreateBinary();
QueueHandle_t xQueueRed = xQueueCreate(1, sizeof(Mode));
QueueHandle_t xQueueGreen = xQueueCreate(1, sizeof(bool));

void tLEDRed(void *p) {
	TickType_t xLastWakeTime = 0;
	int delay = 250;
	Mode mode;
	for (;;) {
		if (xQueueReceive(xQueueRed, &mode, (TickType_t) 0) == pdTRUE) {
			switch (mode){
			case STOPPED:
				delay = 250;
				break;
			case RUNNING:
				delay = 500;
				break;
			case OFFLINE:
				xSemaphoreTake(xSemaphoreRed, (TickType_t) portMAX_DELAY);
				break;
			}
		}
		if (xSemaphoreTake(xSemaphoreRed, (TickType_t) portMAX_DELAY) == pdTRUE) {
			digitalWrite(RED_PIN, HIGH);
			vTaskDelayUntil(&xLastWakeTime, delay);
			digitalWrite(RED_PIN, LOW);
			vTaskDelayUntil(&xLastWakeTime, delay);
			xSemaphoreGive(xSemaphoreRed);
		}
	}
}

void tLEDGreen(void *p) {
	byte leds;
	TickType_t xLastWakeTime = 0;
	bool taken = false;
	bool isStop;
	bool shouteck;
	for (;;) {
		if (taken == false) {
			if (xSemaphoreTake(xSemaphoreGreen, (TickType_t) portMAX_DELAY) == pdTRUE) {
				taken = true;

				leds = 255;
				digitalWrite(LATCH_PIN, LOW);
				shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, leds);
				digitalWrite(LATCH_PIN, HIGH);
				xSemaphoreGive(xSemaphoreGreen);

				isStop = true;
				xQueueOverwrite(xQueueGreen, &isStop);
			}
		}
		else {
			if (xQueueReceive(xQueueGreen, &isStop, (TickType_t) 0) == pdTRUE) {
				shouteck = isStop;
			}
			if (shouteck) {
				leds = 255;
				digitalWrite(LATCH_PIN, LOW);
				shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, leds);
				digitalWrite(LATCH_PIN, HIGH);
				vTaskDelayUntil(&xLastWakeTime, 250);
			} else {
			    leds = 1;
				for (int i = 0; i < 8; i++)
				{
				  digitalWrite(LATCH_PIN, LOW);
				  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, leds << i);
				  digitalWrite(LATCH_PIN, HIGH);
				  vTaskDelayUntil(&xLastWakeTime, 250);
				}
			}
		}
	}
}



