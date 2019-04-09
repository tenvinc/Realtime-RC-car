/*
 * motor.h
 *
 *  Created on: 5 Apr 2019
 *      Author: Vincent
 */

#ifndef MOTOR_H_
#define MOTOR_H_

extern QueueHandle_t xQueueLeft;
extern QueueHandle_t xQueueRight;

void left(void*);

void right(void*);

#endif /* MOTOR_H_ */
