/*
 * constants.h
 *
 *  Created on: 5 Apr 2019
 *      Author: Vincent
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

typedef enum {
	STOPPED = 0,
	RUNNING = 1,
	OFFLINE = -1
} Mode;

typedef enum {
	HELLO = '/',
	BYE = '?',
	FORWARD = 'F',
	REVERSE = 'B',
	STR_LEFT = 'K',
	STR_RIGHT = 'Q',
	LEFT = 'L',
	RIGHT = 'R',
	STOP = 'S'
} Command;

const int RIGHT_REVERSE = 6;
const int RIGHT_FORWARD = 5;
const int LEFT_FORWARD = 9;
const int LEFT_REVERSE = 10;
const int DATA_PIN = 4;
const int LATCH_PIN = 3;
const int CLOCK_PIN = 2;
const int RED_PIN = 13;
const int BUZZER = 8;

#endif /* CONSTANTS_H_ */
