#include "ultrasonic_sensor.h"

void ISR_TC1(void) interrupt 3
{
    // Reseta a flag
    TF1 = 0;
    count_global += 0.00262144;
    if (1 < count_global)
    IE1 = 1;
}

unsigned int le_hcsr04(void)
{
    unsigned int le_pulso_micro;

    TRIG = HIGH; // Trigger
    delay_us(10); // Exigencia do datasheet
    TRIG = LOW;
    le_pulso_micro = (unsigned int)(le_pulso() * 1000000); // segundos para micro, por isso multiplico por x106

    return le_pulso_micro/58;
}
