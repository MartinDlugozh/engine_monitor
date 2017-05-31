//#include <Arduino.h>
//#include <stdarg.h>

#include "RPM_sensor.h"

/**
* Constructor
*/
RPM_sensor::RPM_sensor()
{
#if (HIL_MODE == 1)
	_x = 0;
#endif
	_rpm = 0;
}

/**
* @brief RPM_sensor begin
*/
void RPM_sensor::begin(void)
{
	_pulseCount = 0;
	_rpm = 0;
	_timer = millis();
}

/**
* @brief Accumulation function
* Вызывается по прерыванию от датчика и накапливает данные в внутреннем счетчике
*/
void RPM_sensor::accumulate(void)
{
	_pulseCount++;
}

/**
* @brief Update function
* Вызывается в каждом цикле и выполняется раз в секунду
* Обновляет данные об оборотах двигателя с частотой 1 Гц
*/
void RPM_sensor::update(void)
{
#if (HIL_MODE == 1)
	if (millis() - _timer >= 100)
	{
		_rpm = 10000 - 2000*abs(cos(_x/8));
		_pulseCount = 0;
		_timer = millis();
		(_x <= 254) ? (_x++) : (_x = 0);
	}
#else
	if (millis() - _timer >= 1000)
	{
		_rpm = _pulseCount * 30;
		_pulseCount = 0;
		_timer = millis();
	}
#endif
}

/**
* @brief Get RPM
* Возвращает кол-во оборотов вала двигателя в минуту
* @retval rpm - [об/мин]
*/
uint16_t RPM_sensor::getRPM(void)
{
	return _rpm;
}
