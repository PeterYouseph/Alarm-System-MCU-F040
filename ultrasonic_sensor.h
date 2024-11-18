#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include "def_pinos.h"
#include "delay.h"

#define TRIG P3_0
#define ECHO P3_1
#define LOW 0
#define HIGH 1


unsigned int le_hcsr04(void);

#endif
