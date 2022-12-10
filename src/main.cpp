/*
  Исходники проекта не публикуются до завершения миграции прототипа в проект MKlon2
*/


/*
  https://manualzz.com/doc/11587480/using-atsamd21-sercom-for-more-spi--i2c-and-serial-ports
  Using ATSAMD21 SERCOM for more SPI, I2C and Serial ports

  View detail for Atmel AT11628: SAM D21 SERCOM I2C Configuration

  Вариант со схемой защиты
  12 декабря 2022   -->  v7
  Platform: 7.1.0   --> 8.1.0
  VS: 1.72.1        --> 1.73.1
  C/C++ 1.12.4      --> 1.13.7
  pcb: mcdm.v7.3    --> mklon2v7 (mklon2v5)
*/

#include "board/mpins.h"
#include "wake/wake.h"
#include "commands/commands.h"
#include "power/power_reg.h"
#include "adc/adc.h"
#include "manager.h"
#include "ac/ac_samd21.h"

#include <Arduino.h>            // N. порядок не нарушать!
#include "wiring_private.h"     // N=1.

void setup() 
{
  #ifdef SER_USB
    SerialUSB.begin(115200);                                // Open the native USB port
    while(!SerialUSB);                                      // Wait for the console to open
  #endif
  
  // инициализация UART порта обмена с ESP32 ( D0:PA11/UART-RX, D1:PA10/UART-TX )
  Serial1.begin(230400);            // Проверено
  while(!Serial1);

  portsInit();
  wakeInit(0x00, 5);                // обмен без адреса, время ожидания 5 ms
  initMeasure();
  initPids();                       // 
  initState1();
  initState2();
}

void loop() 
{
    // Измерения и регулирование
    // считать, преобразовать, задать следующее и запустить
  manager();

    // Если в буфере приема есть принятые байты (не факт, что пакет полный), 
    // пока не принят весь пакет, время ожидания ограничено (пока 1с).  
  if(Serial1.available()) {wakeRead();}

  doState1();
  doState2();
  doCommand();                  // Если ненулевая, будет исполнена.
}
