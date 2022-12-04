/*
  My DAC
  https://electronics.stackexchange.com/questions/409136/samd21-dac-example/411040
  Версия от 07 сентября 2022г.
*/

#include "dac/dac.h"
#include <Arduino.h>


void syncDAC()
{
  while (1 == DAC->STATUS.bit.SYNCBUSY);
}

void dacInit()
{
  DAC->CTRLB.reg = 0x40;  // use AVCC as the reference
  syncDAC();
}

void dacWrite10bit(const unsigned short value)
{
  DAC->CTRLB.reg = 0x40;              // DAC off
  DAC->CTRLA.reg = DAC_CTRLA_ENABLE;  // Enable DAC
  syncDAC();
  DAC->DATA.reg  = 0x3FF & value;
  syncDAC();
  DAC->CTRLB.reg = 0x43;              // DAC on
}
