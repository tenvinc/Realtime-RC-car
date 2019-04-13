/*
 * music.cpp
 *
 *  Created on: 4 Apr 2019
 *      Author: Vincent
 */
#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include "constants.h"

#define C3  130.81
#define Db3 138.59
#define D3  146.83
#define Eb3 155.56
#define E3  164.81
#define F3  174.61
#define Gb3 185.00
#define G3  196.00
#define Ab3 207.65
#define LA3 220.00
#define Bb3 233.08
#define B3  246.94
#define C4  261.63
#define Db4 277.18
#define D4  293.66
#define Eb4 311.13
#define E4  329.63
#define F4  349.23
#define Gb4 369.99
#define G4  392.00
#define Ab4 415.30
#define LA4 440.00
#define Bb4 466.16
#define B4  493.88
#define C5  523.25
#define Db5 554.37
#define D5  587.33
#define Eb5 622.25
#define E5  659.26
#define F5  698.46
#define Gb5 739.99
#define G5  783.99
#define Ab5 830.61
#define LA5 880.00
#define Bb5 932.33
#define B5  987.77
#define C6  1046.50

#define BPM 120      // tempo
#define H 2*Q        // half 2/4
#define Q 60000/BPM  // quarter 1/4
#define E Q/2        // eighth 1/8
#define S Q/4        // sixteenth 1/16
#define W 4*Q        // whole 4/4

#define BPM_SHARK 100
#define H_SHARK 2*Q_SHARK        // half 2/4
#define Q_SHARK 60000/BPM_SHARK  // quarter 1/4
#define E_SHARK Q_SHARK/2        // eighth 1/8
#define S_SHARK Q_SHARK/4        // sixteenth 1/16
#define W_SHARK 4*Q_SHARK        // whole 4/4

void starttone() {
	tone(BUZZER, G3, E);
	delay(1 + E); //delay duration should always be 1 ms more than the note in order to separate them.
	tone(BUZZER, C4, E);
	delay(1 + E);
	tone(BUZZER, E4, E);
	delay(1 + E);
	tone(BUZZER, G5, Q);
	delay(1 + Q);
	delay(500);
}

void endtone() {
	tone(BUZZER, G3, E);
	delay(1 + E); //delay duration should always be 1 ms more than the note in order to separate them.
	tone(BUZZER, C4, E);
	delay(1 + E);
	tone(BUZZER, E4, E);
	delay(1 + E);
	tone(BUZZER, G4, E);
	delay(1 + E);
	tone(BUZZER, C5, E);
	delay(1 + E);
	tone(BUZZER, E5, E);
	delay(1 + E);
	tone(BUZZER, G5, Q + E);
	delay(1 + Q + E);
	tone(BUZZER, E5, Q + E);
	delay(1 + Q + E);

	tone(BUZZER, Ab3, E);
	delay(1 + E);
	tone(BUZZER, C4, E);
	delay(1 + E);
	tone(BUZZER, Eb4, E);
	delay(1 + E);
	tone(BUZZER, Ab4, E);
	delay(1 + E);
	tone(BUZZER, C5, E);
	delay(1 + E);
	tone(BUZZER, Eb5, E);
	delay(1 + E);
	tone(BUZZER, Ab5, Q + E);
	delay(1 + Q + E);
	tone(BUZZER, Eb5, Q + E);
	delay(1 + Q + E);

	tone(BUZZER, Bb3, E);
	delay(1 + E);
	tone(BUZZER, D4, E);
	delay(1 + E);
	tone(BUZZER, F4, E);
	delay(1 + E);
	tone(BUZZER, Bb4, E);
	delay(1 + E);
	tone(BUZZER, D5, E);
	delay(1 + E);
	tone(BUZZER, F5, E);
	delay(1 + E);
	tone(BUZZER, Bb5, Q + E);
	delay(1 + Q + E);
	tone(BUZZER, Bb5, E);
	delay(1 + E);
	tone(BUZZER, Bb5, E);
	delay(1 + E);
	tone(BUZZER, Bb5, E);
	delay(1 + E);
	tone(BUZZER, C6, H + Q + E);
	delay(1 + H + Q + E);

	delay(2 * H);
}

void sequence() {
	tone(BUZZER, G4, E_SHARK);
	vTaskDelay(1 + E_SHARK);
	tone(BUZZER, G4, E_SHARK);
	vTaskDelay(1 + E_SHARK);

	tone(BUZZER, G4, E_SHARK);
	vTaskDelay(1 + E_SHARK);
	tone(BUZZER, G4, S_SHARK);
	vTaskDelay(1 + S_SHARK);
	tone(BUZZER, G4, E_SHARK);
	vTaskDelay(1 + E_SHARK);

	tone(BUZZER, G4, S_SHARK);
	vTaskDelay(1 + S_SHARK);
	tone(BUZZER, G4, E_SHARK);
	vTaskDelay(1 + E_SHARK);
}

void tAudio(void* p) {
	for (;;) {
		tone(BUZZER, D3, Q_SHARK);
		vTaskDelay(1 + Q_SHARK);
		tone(BUZZER, E3, Q_SHARK);
		vTaskDelay(1 + Q_SHARK);

		sequence();

		tone(BUZZER, G3, E_SHARK);
		vTaskDelay(1 + E_SHARK);
		tone(BUZZER, G3, E_SHARK);
		vTaskDelay(1 + E_SHARK);

		sequence();

		tone(BUZZER, G3, E_SHARK);
		vTaskDelay(1 + E_SHARK);
		tone(BUZZER, G3, E_SHARK);
		vTaskDelay(1 + E_SHARK);

		sequence();

		tone(BUZZER, G3, E_SHARK);
		vTaskDelay(1 + E_SHARK);
		tone(BUZZER, G3, E_SHARK);
		vTaskDelay(1 + E_SHARK);
		tone(BUZZER, Gb4, H_SHARK);
		vTaskDelay(1 + H_SHARK);
	}
}

