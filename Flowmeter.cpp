#include <Arduino.h>
#include <stdarg.h>

#include "Flowmeter.h"

/**
* Constructor
*/
Flowmeter::Flowmeter(){}

/**
* @brief Flowmeter begin
* @param float flow_factor - ����������� [(��/���)/���]
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
* ���������� �� ���������� �� ������� � ����������� ������ � ���������� ��������
*/
void Flowmeter::accumulate(void)
{
	_pulseCount++;
}


/**
* @brief Update function
* ���������� � ������ ����� � ����������� ��� � ������
* ��������� ������ �� ������� ������� (��� � ������)
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
* ���������� �������� �������� ���������� ����������� � �������� � ������
* @retval RPM - [��/���] 
*/
uint16_t Flowmeter::getRPM(void)
{
	return _rpm;
}

/**
* @brief Get Pulses per Minute
* ���������� ���������� ��������� � ������
* ����������� ��� � ������
* @retval _ppm - ���-�� ��������� �� ������
*/
uint16_t Flowmeter::getPPM(void)
{
	return _ppm;
}

/**
* @brief Get Pulses
* ���������� ���������� �������� �������� ���������
* @retval pulseCount - �������� �������� ���������
*/
uint16_t Flowmeter::getPulses(void)
{
	return _pulseCount;
}

/**
* @brief Get Fuel Flow Rate
* ���������� ������ ������� � ����������� � [��*100/���]
* @retval fflow_rate - [��*100/���]
*/
uint16_t Flowmeter::getFuelFlowRate(void)
{
	return (uint16_t)(_fuel_flow_rate * 100);
}