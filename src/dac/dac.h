/*

  Версия от 07 сентября 2022г.
*/

#ifndef _DAC_H_
#define _DAC_H_

#include "stdint.h"

void dacInit();
void dacWrite10bit(const uint16_t value);

#endif  //_DAC_H_
