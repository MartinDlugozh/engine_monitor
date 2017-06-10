#ifndef INC_H_
#define INC_H_

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
//#define MAVLINK_CHECK_MESSAGE_LENGTH 1
#include "./mavlink_avr/ardupilotmega/mavlink.h"
#include "./mavlink_avr/common/mavlink.h"
#include "./mavlink_avr/protocol.h"
#include "./mavlink_avr/mavlink_helpers.h"
#include "./mavlink_avr/checksum.h"
#include "./mavlink_avr/mavlink_types.h"
#include "mavlink_hlp.h"

/**
 * Parameters and common functions
 */
#include "param_helper.h"
//#include "libraries/Flowmeter.h"
#include "RPM_sensor.h"
#include "Temperature_sensor.h"

#endif /* INC_H_ */
