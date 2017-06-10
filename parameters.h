/**
 * Define your MAV MCU parameters here =)
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#define ONBOARD_PARAM_COUNT 	5

/**
 * Definitions
 */
#define 		DBG_TXT_p		param_values[0]
#define 		FL_AMOUNT_p 	param_values[1]
#define 		FL_FFACT_p 		param_values[2]
#define 		TELEM_UART_p	param_values[3]
#define 		TELEM_INJECT_p 	param_values[4]

/**
 * Parameter names
 * (PROGMEM string literals)
 */
const char param_0[] PROGMEM = "DBG_TXT";			// [0]
const char param_1[] PROGMEM = "FL_AMOUNT";			// [1]
const char param_2[] PROGMEM = "FL_FFACT";			// [2]
const char param_3[] PROGMEM = "TELEM_UART";		// [3]
const char param_4[] PROGMEM = "TELEM_INJECT";		// [4]

/**
 * Parameter names table
 */
const char* const param_table[] PROGMEM = {
		param_0,
		param_1,
		param_2,
		param_3,
		param_4
};

/**
 * Parameter values
 * WARNING: all of the parameters have a type of uint8_t (unsigned char)
 * because of using default Arduino EEPROM library,
 * but receiving from and transmitting to the GCS is using float data type
 */
uint8_t			param_values[ONBOARD_PARAM_COUNT] = {
				0,					// [0]
				0,					// [1]
				0,					// [2]
				0,					// [3]
				0};					// [4]

#endif /* PARAMETERS_H_ */
