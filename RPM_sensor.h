/**
* Application Note
* Класс, обеспечиващий получение данных с датчика оборотов двигателя.
* Расчитан на применение датчика Холла и ДВУХ магнитов на валу.
*
* HIL - Hardware in The Loop Simulation (HIL_MODE in Sensor_board.h) - базируется на генерировании входных данных (raw sensor data), изменяющихся по строго определенному закону.
* Симулируется сразу количество оборотов (опуская счетчик импульсов от датчика) по закону _rpm = 10000 - 1000*abs(cos(_x)), где 0 <= _x <= 255.
**/

#ifndef _RPM_SENSOR_H_
#define _RPM_SENSOR_H_

#include <Arduino.h>

class RPM_sensor
{
public:									
	RPM_sensor();						// конструктор

	void begin(void);					// инициализатор
	void accumulate(void);				// аккумулятор
	void update(void);					// обновление данных раз в секунду
	uint16_t getRPM(void);				// возвращает количество оборотов в минуту

private:
	volatile uint16_t _pulseCount;		// счетчик импульсов; принадлежит аккумулятору; сбрасывается раз в секунду
	volatile uint32_t _timer;			// таймер; принадлежит аккумулятору; сбрасывается раз в секунду
	uint16_t _rpm;						// количество оборотов в минуту; обновляется аккумулятором раз в секунду

#if (HIL_MODE == 1)
	uint8_t _x;
#endif
};

#endif /* _RPM_SENSOR_H_ */
