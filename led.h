#ifndef LED_H_
#define LED_H_

#include "Arduino.h"

#define LED_GREEN				52
#define LED_YELLOW				50
#define LED_RED					53

void led_init(void)
{
	pinMode(LED_GREEN, OUTPUT); 		digitalWrite(LED_GREEN, HIGH);
	pinMode(LED_YELLOW, OUTPUT); 		digitalWrite(LED_YELLOW, HIGH);
	pinMode(LED_RED, OUTPUT); 			digitalWrite(LED_RED, HIGH);
}

void led_no_px_gcs_connection(void)
{
	digitalWrite(LED_GREEN, LOW);
	digitalWrite(LED_YELLOW, LOW);
	digitalWrite(LED_RED, HIGH);
}

void led_px_connection(void)
{
	digitalWrite(LED_GREEN, HIGH);
	digitalWrite(LED_RED, LOW);
}

void led_no_px_connection(void)
{
	digitalWrite(LED_GREEN, LOW);
	digitalWrite(LED_RED, HIGH);
}

bool led_gcs_connection(void)
{
	digitalWrite(LED_YELLOW, HIGH);
	return true;
}

void led_no_gcs_connection(void)
{
	digitalWrite(LED_YELLOW, LOW);
}

#endif /* LED_H_ */
