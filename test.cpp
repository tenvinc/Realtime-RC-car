/*
 * main.cpp
 *
 *  Created on: 19 Mar 2019
 *      Author: Vincent
 */

#include <avr/io.h>
#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

#include "music.h"
#include "motor.h"
#include "leds.h"
#include "constants.h"

#define STACK_SIZE 200
#define TIMEOUT 1000

void tSerial(void *p) {
	int l = 0;
	int r = 0;
	Mode mode = OFFLINE;
	bool isStop = false;
	TickType_t xLastWakeTime = 0;
	unsigned long previousActiveTime = 0;
	for (;;) {
		if (Serial.available()) {
			char c = Serial.read();
			switch (c) {
			case HELLO:
				byte leds;
				for (int i = 0; i < 2; i++) {
					leds = 255;

					digitalWrite(LATCH_PIN, LOW);
					shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, leds);
					digitalWrite(LATCH_PIN, HIGH);
					delay(500);

					leds = 0;

					digitalWrite(LATCH_PIN, LOW);
					shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, leds);
					digitalWrite(LATCH_PIN, HIGH);
					delay(500);
				}
				starttone();
				// Do the wake up
				xSemaphoreGive(xSemaphoreGreen);
				xSemaphoreGive(xSemaphoreRed);
				break;
			case BYE:
				mode = OFFLINE;
				xQueueOverwrite(xQueueRed, &mode);
				endtone();
				break;
			case STR_LEFT:
				l = -255;
				r = 255;
				mode = RUNNING;
				xQueueOverwrite(xQueueRed, &mode);
				isStop = false;
				xQueueOverwrite(xQueueGreen, &isStop);
				previousActiveTime = millis();
				break;
			case LEFT:
				l = 95;
				r = 255;
				mode = RUNNING;
				xQueueOverwrite(xQueueRed, &mode);
				isStop = false;
				xQueueOverwrite(xQueueGreen, &isStop);
				previousActiveTime = millis();
				break;
			case STR_RIGHT:
				l = 255;
				r = -255;
				mode = RUNNING;
				xQueueOverwrite(xQueueRed, &mode);
				isStop = false;
				xQueueOverwrite(xQueueGreen, &isStop);
				previousActiveTime = millis();
				break;
			case RIGHT:
				l = 255;
				r = 95;
				mode = RUNNING;
				xQueueOverwrite(xQueueRed, &mode);
				isStop = false;
				xQueueOverwrite(xQueueGreen, &isStop);
				previousActiveTime = millis();
				break;
			case FORWARD:
				l = 255;
				r = 255;
				mode = RUNNING;
				xQueueOverwrite(xQueueRed, &mode);
				isStop = false;
				xQueueOverwrite(xQueueGreen, &isStop);
				previousActiveTime = millis();
				break;
			case REVERSE:
				l = -255;
				r = -255;
				mode = RUNNING;
				xQueueOverwrite(xQueueRed, &mode);
				isStop = false;
				xQueueOverwrite(xQueueGreen, &isStop);
				previousActiveTime = millis();
				break;
			case STOP:
				l = 0;
				r = 0;
				mode = STOPPED;
				xQueueOverwrite(xQueueRed, &mode);
				isStop = true;
				xQueueOverwrite(xQueueGreen, &isStop);
				previousActiveTime = millis();
				break;
			}
			xQueueSend(xQueueLeft, &l, (TickType_t) 0);
			xQueueSend(xQueueRight, &r, (TickType_t) 0);
		}else if (millis() - previousActiveTime > 500) {
			l = 0;
			r = 0;
			xQueueSend(xQueueLeft, &l, (TickType_t) 0);
			xQueueSend(xQueueRight, &r, (TickType_t) 0);
			mode = STOPPED;
			xQueueOverwrite(xQueueRed, &mode);
			isStop = true;
			xQueueOverwrite(xQueueGreen, &isStop);
		}
		vTaskDelayUntil(&xLastWakeTime, 40);
	}
}

void setup() {
	pinMode(LEFT_FORWARD, OUTPUT);
	pinMode(LEFT_REVERSE, OUTPUT);
	pinMode(RIGHT_FORWARD, OUTPUT);
	pinMode(RIGHT_REVERSE, OUTPUT);
	pinMode(DATA_PIN, OUTPUT);
	pinMode(CLOCK_PIN, OUTPUT);
	pinMode(LATCH_PIN, OUTPUT);
	pinMode(RED_PIN, OUTPUT);
	Serial.begin(9600);
}

void loop() {
	xTaskCreate(tMotorControlLeft, "left", 100, NULL, 4, NULL);
	xTaskCreate(tMotorControlRight, "right", 100, NULL, 4, NULL);
	xTaskCreate(tSerial, "bluetooth", 200, NULL, 5, NULL);
    xTaskCreate(tLEDGreen, "Green led", 100, NULL, 2, NULL);
    xTaskCreate(tLEDRed, "Red led", 100, NULL, 1, NULL);
    xTaskCreate(tAudio, "BabyShark", 100, (void *)BUZZER, 3, NULL);
    xSemaphoreTake(xSemaphoreGreen, 0);
	vTaskStartScheduler();
}
