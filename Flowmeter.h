#ifndef _FLOWMETER_H_
#define _FLOWMETER_H_

#include <Arduino.h>

class Flowmeter
{
public:
	Flowmeter(); 									  // �����������

	void begin(float);	  							  // �������������: ����������� [(��/���)/��] 
	void accumulate(void);							  // �����������
	void update(void);								  // ���������� ������ ��� � ������
	uint16_t getRPM(void);							  // ���������� ���������� �������� � ������ ���������� �����������
	uint16_t getFuelFlowRate(void);					  // ���������� ������ ������� � [��*100/���]
	uint16_t getPPM(void);							  // ���������� ����� ��������� � ������
	uint16_t getPulses(void);						  // ���������� ���������� �������� �������� ���������

private:
	float _flow_factor;						   		  // �����������[(�� / ���) / ��]
	volatile uint16_t _pulseCount;					  // ������� ���������; ����������� ������������; ������������ ��� � �������
	volatile uint32_t _timer;						  // ������; ����������� ������������; ������������ ��� � �������
	uint16_t _rpm;									  // ���������� �������� � ������; ����������� ������������� ��� � �������
	float _fuel_flow_rate;							  // ������ ������� � [��/���]; ����������� ������������� ��� � �������
	uint16_t _ppm;									  // ����� ��������� � ������

#if (HIL_MODE == 1)
	uint8_t _x;
#endif
};

#endif /* _FLOWMETER_H_ */
