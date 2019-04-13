/*
 * leds.h
 *
 *  Created on: 5 Apr 2019
 *      Author: Vincent
 */

#ifndef LEDS_H_
#define LEDS_H_

extern SemaphoreHandle_t xSemaphoreGreen;
extern SemaphoreHandle_t xSemaphoreRed;

extern QueueHandle_t xQueueGreen;
extern QueueHandle_t xQueueRed;

void tLEDRed(void*);
void tLEDGreen(void*);

#endif /* LEDS_H_ */
