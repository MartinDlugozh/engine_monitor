/**
* Application Note
* Класс, обеспечиващий получение данных с датчика температуры типа термистор.
* Вычисление температуры производится согласно приведенному уравнению Стейнхарта — Харта.
*
* HIL - Hardware in The Loop Simulation (HIL_MODE in Sensor_board.h) - базируется на генерировании входных данных (raw sensor data), изменяющихся по строго определенному закону.
* Данные симуляци, смоделированные в системе MatLab должны совпадать с результатами симуляции на контроллере.
**/

#ifndef _TEMPERATURE_SENSOR_H_
#define _TEMPERATURE_SENSOR_H_

#include "Arduino.h"

class Temperature_sensor
{
public:
	Temperature_sensor();							 // конструктор

	void begin(float, uint8_t);						 // инициализатор: балласт, аналоговый вход
	void accumulate(void);							 // аккумулятор
	void update(void);
	float getTemperature(void);					 // возвращает значение температуры двигателя в [град. С * 100]

private:
	uint8_t _pin;									 // аналоговый вход, к которому подключен термистор; принадлежит аккумулятору
	float _bal_res;									 // сопротивление балластного резистора в омах; принадлежит аккумулятору
	float _temperature;								 // значение температуры в [град. С]; обновляется аккумулятором раз в 0,1 секунды (10 Гц)
	uint32_t _timer;								 // таймер; принадлежит аккумулятору; сбрасывается раз в 0,1 секунды (10 Гц)
#if (HIL_MODE == 1)
	uint16_t _x;
#endif
};

#endif /* _TEMPERATURE_SENSOR_H_ */
