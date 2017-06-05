#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2017-06-05 15:45:36

#include "Arduino.h"
#include "Arduino.h"
#include "TaskScheduler.h"
#include "HardwareSerial.h"
#include <avr/pgmspace.h>
#include "mc_config.h"
#include "mc_var.h"
#include "led.h"
#include "./mavlink_avr/ardupilotmega/mavlink.h"
#include "./mavlink_avr/common/mavlink.h"
#include "./mavlink_avr/protocol.h"
#include "./mavlink_avr/mavlink_helpers.h"
#include "./mavlink_avr/checksum.h"
#include "./mavlink_avr/mavlink_types.h"
#include "mavlink_hlp.h"
#include "parameters.h"
#include "RPM_sensor.h"
#include "Temperature_sensor.h"
void rpm_int() ;
void setup() ;
void loop() ;
void loop_imm(void) ;
void loop_50Hz(void) ;
void loop_2Hz(void) ;
void loop_1Hz(void) ;

#include "engine_monitor_s.ino"


#endif
