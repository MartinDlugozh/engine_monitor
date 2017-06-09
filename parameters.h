/**
 * Параметры, хранимые в постоянной памяти EEPROM.
 * Порядок заполнения:
 * 1. Значение ONBOARD_PARAM_COUNT увеличить в сответствии с количеством
 * добавляемых параметров;
 * 2. Дописать имена параметров в массив const char *param_names[ONBOARD_PARAM_COUNT];
 * 3. Дописать в массив uint8_t	param_values[ONBOARD_PARAM_COUNT] значение инициализации
 * для добавляемых параметров (рекомендуется заполнять нулями);
 * 4. Для добавляемых параметров добавить дефайны для связи имен и значений (для удобочитаемости)
 * #define name_n param_values[n]
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include <EEPROM.h>
#include <avr/pgmspace.h>

#define ONBOARD_PARAM_COUNT 5

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
 */
/**
 * Parameter names
 */
const char param_0[] PROGMEM = "DBG_TXT";			// [0]
const char param_1[] PROGMEM = "FL_AMOUNT";			// [1]
const char param_2[] PROGMEM = "FL_FFACT";			// [2]
const char param_3[] PROGMEM = "TELEM_UART";		// [3]
const char param_4[] PROGMEM = "TELEM_INJECT";		// [4]

const char* const param_table[] PROGMEM = {
		param_0,
		param_1,
		param_2,
		param_3,
		param_4
};

/**
 * Parameter values
 * WARNING: all of the parameters have a type of uint8_t (unsigned char),
 * but receiving from and transmitting to the GCS is using float data type
 */
uint8_t			param_values[ONBOARD_PARAM_COUNT] = {
				0,					// [0]
				0,					// [1]
				0,					// [2]
				0,					// [3]
				0};					// [4]

/**
 * Load parameter names from PROGMEM
 */
char buffer[16] = {0};

char *get_by_index(uint8_t param_index)// char* param, char _buffer[]
{
	memset(buffer, 0, 16);
	return strcpy_P(buffer, (char*)pgm_read_word(&(param_table[param_index])));
}

/**
 * Load all parameters from EEPROM
 */
void param_load_all()
{
	for (uint8_t i = 0; i < ONBOARD_PARAM_COUNT; i++)
	{
		param_values[i] = EEPROM.read(i);
	}
}

/**
 * Save all parameters to EEPROM
 */
void param_save_all()
{
	for (uint8_t i = 0; i < ONBOARD_PARAM_COUNT; i++)
	{
		EEPROM.write(i, param_values[i]);
	}
}

/**
 * Send single parameter by param_index
 */
void param_send(uint8_t param_index, HardwareSerial &uart)
{
	mavlink_message_t p_msg;

	mavlink_msg_param_value_pack(MY_SYS_ID, MY_COMP_ID, &p_msg,
			get_by_index(param_index)
			, (float)param_values[param_index],
			MAV_PARAM_TYPE_REAL32, (uint16_t)ONBOARD_PARAM_COUNT, (uint16_t)param_index);
	send_message(&p_msg, uart);
}

/**
 * Handle MAVLink message PARAM_SET
 * Save received parameter to the EEPROM and replace value of param_values[i]
 */
void param_handle_set(mavlink_param_set_t parameter, HardwareSerial &uart)
{
	for (uint8_t i = 0; i < ONBOARD_PARAM_COUNT; i++)
	{
		if(strcmp(get_by_index(i), parameter.param_id) == 0)
		{
			param_values[i] = (uint8_t)parameter.param_value;
			EEPROM.write(i, param_values[i]);

			param_send(i, uart);

			if(DBG_TXT_p == 1)
			{
				statustext_send("PARAM_SAVED", uart);
			}
			break;
		}
	}
}

/**
 * Send all parameters when requested
 */
void param_handle_req_list(HardwareSerial &uart)
{
	for (uint8_t i = 0; i < ONBOARD_PARAM_COUNT; i++)
	{
		param_send(i, uart);
	}
}

/**
 * Send single parameter when it is requested
 */
void param_handle_req_value(mavlink_param_request_read_t rq, HardwareSerial &uart)
{
	if(rq.param_index == (-1))
	{
		for (uint8_t i = 0; i < ONBOARD_PARAM_COUNT; i++)
			{
				if(strcmp(get_by_index(i), rq.param_id) == 0)
				{
					param_send(i, uart);
					break;
				}
			}
	}else
	{
		param_send((uint8_t)rq.param_index, uart);
	}
}

#endif /* PARAMETERS_H_ */
