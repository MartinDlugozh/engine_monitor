#include <math.h>
#include "Temperature_sensor.h"

/**
* Constructor
*/
Temperature_sensor::Temperature_sensor()
{
	_timer = 0;
	_bal_res = 1;
	_pin = 0;
	_temperature = 0;
}

/**
* @brief Temperature_sensor begin
* @param float bal_res - сопротивление балластного резистора
* @param float therm_res - сопротивление термистора
* @param uint8_t pin - аналоговый вход термистора
*/
void Temperature_sensor::begin(float bal_res, uint8_t pin)
{
	_bal_res = bal_res;
	_pin = pin;
	_timer = millis();
	_temperature = 0;
#if (HIL_MODE == 1)
	_x = 0;
#endif
}

/**
* @brief Accumulation function
*/
void Temperature_sensor::accumulate(void)
{
#if (HIL_MODE == 1)
	_temperature = log(_bal_res*((1024.0f / _x) - 1) + 0.1f);
	_temperature = ((1 / (0.001129148f + (0.000234125f * _temperature) + (0.0000000876741f * _temperature * _temperature * _temperature))) - 305.15f) / 1.8f;

	(_x <= 1024) ? (_x++) : (_x = 0);
#else
	_temperature = log(_bal_res*((1024.0f / analogRead(_pin)) - 1));
	//log(10000.0*((1024.0/RawADC-1)));
	_temperature = 1.0f / (0.001129148f + (0.000234125f + (0.0000000876741f * _temperature * _temperature ))* _temperature );
	_temperature = _temperature - 273.15f;
//	_temperature = (_temperature * 9.0f)/ 5.0f + 32.0f;//+32
	//_temperature = _temperature + 273.15f;
	//((1 / (0.001129148 + (0.000234125 * _temperature) + (0.0000000876741 * _temperature * _temperature * _temperature))) - 305.15) / 1.8f;
#endif
}

/**
* @brief Update function
* Обновляет данные о температуре с частотой 10 Гц
*/
void Temperature_sensor::update(void)
{
	if ((millis() - _timer) >= 100)
	{
		accumulate();
		_timer = millis();
	}
}

/**
* @brief Get Temperature
* Возвращает температуру двигателя в [град. С * 100]
* @retval temperature - [град. С * 100]
*/
float Temperature_sensor::getTemperature(void)
{
	return (_temperature);
}
