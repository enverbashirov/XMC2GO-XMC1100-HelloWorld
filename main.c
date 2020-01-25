#include <DAVE.h> // Declarations from DAVE Code Generation (includes SFR declaration)
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

// ***** defines: *****
#define ON 1
#define OFF 0

// ***** Global Variables: *****
// LED Status
bool bLed0 = OFF;
bool bLed1 = OFF;

// SoftwareTimer:
#define INTERVAL 100000U // 100ms

// Tick Counter
unsigned int iTickCounter = 0;

// ***** function prototypes: *****
// LEDs:
void LED0ON (void);
void LED0OFF (void);
void LED0TOGGLE (void);
void LED1ON (void);
void LED1OFF (void);
void LED1TOGGLE (void);
void LEDSequence (void); // LED Sequence

int main(void)	{
	uint32_t SoftwareTimer;
	SYSTIMER_STATUS_t statusSYSTIMER;

	DAVE_Init(); // Initialization of DAVE APPs

	SoftwareTimer = (uint32_t)SYSTIMER_CreateTimer(INTERVAL,SYSTIMER_MODE_PERIODIC,(void*)LEDSequence,NULL);
	if (SoftwareTimer != 0U) {
		;
	}
	else {
		while (1); // Software timer creation is failed
	}
	statusSYSTIMER = SYSTIMER_StartTimer(SoftwareTimer);
	if (statusSYSTIMER == SYSTIMER_STATUS_SUCCESS) {
		; // Software timer is running
	}
	else {
		while (1); // Error during Software timer start operation
	}

	while(1U);
}

// LED Sequence
void LEDSequence (void) {
	//SHORT: 1 LONG: 3 PAUSE_LETTER: 3 PAUSE_WORD: 7
	switch (iTickCounter) {
		// PAUSE_WORD: 7
		//H ....
		case 7: LED0ON(); break;
		case 9: LED0ON(); break;
		case 11: LED0ON(); break;
		case 13: LED0ON(); break;
		// PAUSE_LETTER: 3
		//E .
		case 17: LED0ON(); break;
		// PAUSE_LETTER: 3
		//L	.-..
		case 21: LED0ON(); break;
		case 23 ... 25: LED0ON(); break;
		case 27: LED0ON(); break;
		case 29: LED0ON(); break;
		// PAUSE_LETTER: 3
		//L	.-..
		case 33: LED0ON(); break;
		case 35 ... 37: LED0ON(); break;
		case 39: LED0ON(); break;
		case 41: LED0ON(); break;
		// PAUSE_LETTER: 3
		//O	---
		case 45 ... 47: LED0ON(); break;
		case 49 ... 51: LED0ON(); break;
		case 53 ... 55: LED0ON(); break;
		// PAUSE_WORD: 7
		//W	.--
		case 63: LED0ON(); break;
		case 65 ... 67: LED0ON(); break;
		case 69 ... 71: LED0ON(); break;
		// PAUSE_LETTER: 3
		//O	---
		case 75 ... 77: LED0ON(); break;
		case 79 ... 81: LED0ON(); break;
		case 83 ... 85: LED0ON(); break;
		// PAUSE_LETTER: 3
		//R	.-.
		case 89: LED0ON(); break;
		case 91 ... 93: LED0ON(); break;
		case 95: LED0ON(); break;
		// PAUSE_LETTER: 3
		//L	.-..
		case 99: LED0ON(); break;
		case 101 ... 103: LED0ON(); break;
		case 105: LED0ON(); break;
		case 107: LED0ON(); break;
		// PAUSE_LETTER: 3
		//D	-..
		case 111 ... 113: LED0ON(); break;
		case 115: LED0ON(); break;
		case 117: LED0ON(); break;

		// PAUSE_LETTER: 7
		//S	...
		case 125: LED1ON(); break;
		case 127: LED1ON(); break;
		case 129: LED1ON(); break;

		// PAUSE_WORD: 3
		//O	---
		case 133 ... 135: LED1ON(); break;
		case 137 ... 139: LED1ON(); break;
		case 141 ... 143: LED1ON(); break;

		// PAUSE_WORD: 3
		//S	...
		case 147: LED1ON(); break;
		case 149: LED1ON(); break;
		case 151: LED1ON(); break;

		// BLINKING NOT-SYNCHRONOUS
		case 159: LED0TOGGLE(); break;
		case 160 ... 178: LED0TOGGLE(), LED1TOGGLE(); break;

		// TIMER RESET
		case 180: iTickCounter = 0; break;
		default: LED0OFF(), LED1OFF(); break;
	}
	iTickCounter++;
}

void LED0ON (void) {
	DIGITAL_IO_SetOutputHigh(&LED_P1_P0);
	bLed0 = ON;
}
void LED0OFF (void) {
	DIGITAL_IO_SetOutputLow(&LED_P1_P0);
	bLed0 = OFF;
}
void LED0TOGGLE (void) {
	if (bLed0 == OFF)
		LED0ON();
	else
		LED0OFF();
}
void LED1ON (void) {
	DIGITAL_IO_SetOutputHigh(&LED_P1_P1);
	bLed1 = ON;
}
void LED1OFF (void) {
	DIGITAL_IO_SetOutputLow(&LED_P1_P1);
	bLed1 = OFF;
}
void LED1TOGGLE (void) {
	if (bLed1 == OFF)
		LED1ON();
	else
		LED1OFF();
}
