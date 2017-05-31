#include <Arduino.h>
#include <stdarg.h>

#include "Flowmeter.h"

/**
* Constructor
*/
Flowmeter::Flowmeter(){}

/**
* @brief Flowmeter begin
* @param float flow_factor - коэффициент [(мл/мин)/имп]
*/
void Flowmeter::begin(float flow_factor)
{
	_flow_factor = flow_factor;
	_pulseCount = 0;
	_rpm = 0;
	_timer = millis();
}

/**
* @brief Accumulation function
* Вызывается по прерыванию от датчика и накапливает данные в внутреннем счетчике
*/
void Flowmeter::accumulate(void)
{
	_pulseCount++;
}


/**
* @brief Update function
* Вызывается в каждом цикле и выполняется раз в минуту
* Обновляет данные по расходу топлива (раз в минуту)
*/
void Flowmeter::update(void)
{
#if (HIL_MODE == 1)
	if (millis() - _timer >= 100)
	{
		_pulseCount = 1000;
		_rpm = _pulseCount / 2;
		_fuel_flow_rate = _pulseCount * _flow_factor;
		_ppm = _pulseCount;
		_timer = millis();
	}
#else
	if (millis() - _timer >= 60000)
	{
		_rpm = _pulseCount / 2;
		_fuel_flow_rate = _pulseCount * _flow_factor;
		_ppm = _pulseCount;
		_pulseCount = 0;
		_timer = millis();
	}
#endif
}

/**
* @brief Get RPM
* Возвращает скорость вращения крыльчатки расходомера в оборотах в минуту
* @retval RPM - [об/мин] 
*/
uint16_t Flowmeter::getRPM(void)
{
	return _rpm;
}

/**
* @brief Get Pulses per Minute
* Возвращает количество импульсов в минуту
* Обновляется раз в минуту
* @retval _ppm - кол-во импульсов за минуту
*/
uint16_t Flowmeter::getPPM(void)
{
	return _ppm;
}

/**
* @brief Get Pulses
* Возвращает мгновенное значение счетчика импульсов
* @retval pulseCount - значение счетчика импульсов
*/
uint16_t Flowmeter::getPulses(void)
{
	return _pulseCount;
}

/**
* @brief Get Fuel Flow Rate
* Возвращает расход топлива в миллилитрах в [мл*100/мин]
* @retval fflow_rate - [мл*100/мин]
*/
uint16_t Flowmeter::getFuelFlowRate(void)
{
	return (uint16_t)(_fuel_flow_rate * 100);
}