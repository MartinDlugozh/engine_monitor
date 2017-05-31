#ifndef MC_CONFIG_H_
#define MC_CONFIG_H_

#define UART_0 					Serial					// Номера портов - основной
#define UART_1 					Serial1					// Номера портов - отладочный
#define UART_2					Serial2
#define UART_3					Serial3
#define UART_DEF				UART_2

#define BAUD_38					38400
#define BAUD_57					57600
#define BAUD_115				115200
#define BAUD_DEF				BAUD_115					// Скорость порта для соединения с автопилотом

#define GCS_SYS_ID				255
#define MY_SYS_ID				99						// SYSTEM_ID микроконтроллера
#define MY_COMP_ID				0						// COMPONNENT_ID микроконтроллера

/*************************************************************************************************/
#define RPM_SENSOR_INT					2					 // номер прерывания для датчика оборотов (2)
#define FFLOWMETER_SENSOR_INT			1					 // номер прерывания для расходомера (3)
#define TEMPERATURE_SENSOR_PIN			A1					 // номер ножки аналогового входа термистора

#define FLOW_FACTOR						0.0562f				 // коэффициент [(мл/мин)/имп] расходомера
#define THERMISTOR_BALANCE_RES			9900.0f				 // сопротивление балластного резистора в омах
#endif /* MC_CONFIG_H_ */
