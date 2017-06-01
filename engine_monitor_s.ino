#define MAVLINK_COMM_NUM_CHANNELS 1
#define MAVLINK_COMM_NUM_BUFFERS 1

/**
 * Arduino inbuild headers
 */
#include "Arduino.h"
#include "TaskScheduler.h"
#include "HardwareSerial.h"
#include <avr/pgmspace.h>

/**
 * Board and software sepcific headers
 */
#include "mc_config.h"
#include "mc_var.h"
#include "led.h"

/**
 * MAVLink headers
 */
//#include "../libraries/mavlink-c-lib/common/mavlink.h"
#include "./mavlink/ardupilotmega/mavlink.h"
#include "./mavlink/common/mavlink.h"
#include "mavlink_hlp.h"

/**
 * Parameters and common functions
 */
#include "parameters.h"
//#include "libraries/Flowmeter.h"
#include "RPM_sensor.h"
#include "Temperature_sensor.h"

/**
 * Main source headers
 */
void loop_imm(void);
void loop_50Hz(void);
void loop_2Hz(void);
void loop_1Hz(void);
//static inline void serial_init(uint8_t uart_number);

Scheduler runner;
//Tasks
Task _1Hz(1000, TASK_FOREVER, &loop_1Hz);
Task _2Hz(500, TASK_FOREVER, &loop_2Hz,  &runner, true, led_gcs_connection, led_no_gcs_connection);
Task _50Hz(20, TASK_FOREVER, &loop_50Hz);

/**
 * Main loop timers
 */
struct {
	volatile uint32_t px_connection;
	volatile uint32_t gcs_connection;
}timer = { 0, 0 };

RPM_sensor				rpm_sensor;								// создаем объекты: датчика оборотов
Temperature_sensor		temp_sensor;							// датчика температуры двигателя
void rpm_int() {rpm_sensor.accumulate();}						// ЭТО КОСТЫЛЬ, СУЦККО	(если по-человечески, то ссылка на эту ф-цию должна быть в объявлении обработчика прерывания)


void setup()
{
	led_init();
	UART_DEF.begin(BAUD_DEF);

	delay(5000);

	param_load_all();
//	param_save_all();
//	param_handle_req_list(UART_DEF);

	rpm_sensor.begin();											// если инициализировали датчик, то у него стартанул таймер
	temp_sensor.begin(THERMISTOR_BALANCE_RES, TEMPERATURE_SENSOR_PIN);

	attachInterrupt(0, rpm_int, FALLING);			// поэтому не медлим и сразу вешаем ему обработчик прерывания

	if(DBG_TXT_p == 1)
	{
		statustext_send("MC is READY", UART_DEF);
	}
	led_no_px_gcs_connection();

	runner.init();
	runner.addTask(_1Hz);
	runner.addTask(_2Hz);
	runner.addTask(_50Hz);

	_1Hz.enable();
//	_2Hz.enable();
	_2Hz.delay(2000);
	_50Hz.enable();
}

void loop()
{
	loop_imm();
	runner.execute();
}

void loop_imm(void)
{
	if(UART_DEF.available() > 0)
	{
		mavlink_message_t rd;
		mavlink_status_t status;

		do{ 				 //если приняты данные
			uint8_t c = UART_DEF.read();					 //читаем

			if (mavlink_parse_char(MAVLINK_COMM_0, c, &rd, &status))
			{
				/**
				 * Обработка данных от наземной станции
				 * Прием параметров
				 */
				if(rd.sysid == GCS_SYS_ID)
				{
					switch (rd.msgid)
					{
					case MAVLINK_MSG_ID_HEARTBEAT:
					{
						if(gcs_connected == 0)
						{
							gcs_connected = 1;
							_2Hz.enable();
//							led_gcs_connection();
							//delay(2000);
						}
						timer.gcs_connection = millis();
						break;
					}
					case MAVLINK_MSG_ID_PARAM_SET:
					{
						if(DBG_TXT_p == 1)
						{
							statustext_send("GOT_SOME_PARAM", UART_DEF);
						}

						mavlink_param_set_t param;

						mavlink_msg_param_set_decode(&rd, &param);
						param_handle_set(param, UART_DEF);
						break;
					}
					case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
					{
						param_handle_req_list(UART_DEF);
						if(DBG_TXT_p == 1)
						{
							statustext_send("GOT_PARAM_LIST_REQ", UART_DEF);
						}
						break;
					}
					case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
					{
						mavlink_param_request_read_t prq;
						mavlink_msg_param_request_read_decode(&rd, &prq);
						param_handle_req_value(prq, UART_DEF);
						if(DBG_TXT_p == 1)
						{
							statustext_send("GOT_PARAM_VAL_REQ", UART_DEF);
						}
						break;
					}
					default:
						break;
					}
				}else{
					switch(rd.msgid)
					{
					case MAVLINK_MSG_ID_HEARTBEAT:
					{
						if(px_connected == 0)
						{
							px_connected = 1;
							led_px_connection();
						}
						timer.px_connection = millis();
						break;
					}
					default:
						break;
					}
				}
			}
		}while(UART_DEF.available() > 0);
	}
}

void loop_50Hz(void)
{
	rpm_sensor.update();	// вызываем обновление данных по оборотам (внутренний 1 Гц таймер)
	temp_sensor.update();	// вызываем обновление данных по температуре (10 Гц)
}

void loop_2Hz(void)
{
	mavlink_message_t ch;
	mavlink_msg_rc_channels_pack(MY_SYS_ID, MY_COMP_ID, &ch, millis(), (uint8_t)0,
			(uint16_t)rpm_sensor.getRPM(),					// [1]
			(uint16_t)temp_sensor.getTemperature(),			// [2]
			(uint16_t)0,									// [3]
			(uint16_t)0,									// [4]
			(uint16_t)10,									// [5]
			(uint16_t)20,									// [6]
			(uint16_t)30,									// [7]
			(uint16_t)40,									// [8]
			(uint16_t)0,									// [9]
			(uint16_t)0,									// [10]
			(uint16_t)0,									// [11]
			(uint16_t)0,									// [12]
			(uint16_t)0,									// [13]
			(uint16_t)0,									// [14]
			(uint16_t)0,									// [15]
			(uint16_t)0,									// [16]
			(uint16_t)0,									// [17]
			(uint16_t)0,									// [18]
			(uint8_t)255);
	send_message(&ch, UART_DEF);
}

void loop_1Hz(void)
{
	heartbeat_send(UART_DEF);
	systime_send(UART_DEF);

	if((millis() - timer.px_connection) > 5000)
	{
		led_no_px_connection();
		px_connected = 0;
	}

	if((millis() - timer.gcs_connection) > 2000)
	{
//		led_no_gcs_connection();
		gcs_connected = 0;
		_2Hz.disable();
	}
}
