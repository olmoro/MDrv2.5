/*
  
 * Версия от 14 октября 2022г.
*/

    //#include "wiring_private.h"
#include "board/mboard.h"
#include "board/mpins.h"
#include "dac/dac.h"
#include <Arduino.h>

  // state1 - состояния, true - включено:
extern bool switchStatus;           // коммутатор нагрузки ( sw_pin   )
extern bool powerStatus;            // преобразователь     (  )
extern bool currentControlStatus;   // регулирование по току
extern bool voltageControlStatus;   // регулирование по напряжению
extern bool chargeStatus;           // заряд               (  )
extern bool dischargeStatus;        // разряд (тот же вывод, !chargeStatus )
extern bool modeAutoStatus;         // nu
extern bool pidStatus;              // pid-управление регулятором

  // Включение силовых ключей
void swPinOn()
{
  digitalWrite( MPins::sw_pin, LOW );
  switchStatus = true;
}

  // Выключение силовых ключей
void swPinOff()
{
  digitalWrite( MPins::sw_pin, HIGH );
  switchStatus = false;
}

void test1L()  { digitalWrite( MPins::test1, LOW  ); }  // Включение тестового вывода
void test1H() { digitalWrite( MPins::test1, HIGH ); }  // Отключение  тестового вывода

void test2L()  { digitalWrite( MPins::test2, LOW  ); }  // Включение тестового вывода
void test2H() { digitalWrite( MPins::test2, HIGH ); }  // Отключение  тестового вывода

// void test3L()  { digitalWrite( MPins::test3, LOW  ); }  // Включение тестового вывода
// void test3H() { digitalWrite( MPins::test3, HIGH ); }  // Отключение  тестового вывода

  // Инициализация дискретных портов
void portsInit()
{
  pinMode( MPins::test1,  OUTPUT);  
  pinMode( MPins::test2,  OUTPUT);
  // pinMode( MPins::test3,  OUTPUT);
  pinMode( MPins::sw_pin, OUTPUT);
   
  #ifdef WEMOS    // using pcb SAMD21 MINI
    pinMode( MPins::led_rx, OUTPUT);  // led_rx   = 25   no   PB03/LED1 (LED_BUILTIN, LED_RX)
    pinMode( MPins::led_tx, OUTPUT);  // led_tx   = 26   no   PA27/LED2 (LED_TX)
  #endif

// https://wikihandbk.com/wiki/Arduino:%D0%A5%D0%B0%D0%BA%D0%B8%D0%BD%D0%B3/%D0%94%D0%BE%D0%B1%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5_%D0%BF%D0%BE%D1%81%D0%BB%D0%B5%D0%B4%D0%BE%D0%B2%D0%B0%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D1%8B%D1%85_%D0%B8%D0%BD%D1%82%D0%B5%D1%80%D1%84%D0%B5%D0%B9%D1%81%D0%BE%D0%B2_(SERCOM%E2%80%99%D0%BE%D0%B2)_%D0%BD%D0%B0_SAMD-%D0%BF%D0%BB%D0%B0%D1%82%D1%83_Arduino?ysclid=l9jlf9bruf316324363
//  pinPeripheral(MPins::ac0_pin, PIO_AC_CLK);
  //pinMode(MPins::ac0_pin, OUTPUT);
  //pinMode(MPins::ac1_pin, OUTPUT);

  swPinOff();               // Силовые ключи нагрузки отключены
  test1L();
  test2L();                 //
  // test3L();                 //
  dacInit();                // Set reference
  dacWrite10bit( 0x0000 );  //
}

  // Конфигурация режимов
void configMode(uint8_t mode)
{
  switch ( mode )
  {
  case 1:                             // U - регулирование по напряжению
    //chargeStatus = true;              // коммутатор на заряд
    //dischargeStatus = !chargeStatus;
    powerStatus = true;               // преобразователь включить
//    powPinOn();
    switchStatus = true;              // к клеммам подключить
    swPinOn();
  break;

  case 2:                             // I - регулирование по току заряда
    //chargeStatus = true;              // коммутатор на заряд
    //dischargeStatus = !chargeStatus;
    powerStatus = true;               // преобразователь включить
//    powPinOn();
    switchStatus = true;              // к клеммам подключить
    swPinOn();
  break;

  case 3:                             // D - регулирование по току разряда
    //dischargeStatus = true;           // коммутатор на заряд
    //chargeStatus = !dischargeStatus;
    powerStatus = false;              // преобразователь выключить
//    powPinOff();
    switchStatus = true;              // к клеммам подключить
    swPinOn();
  break;

  default:    // OFF
    //chargeStatus = true;              // коммутатор на заряд
    //dischargeStatus = !chargeStatus;
    powerStatus = false;              // преобразователь выключить
//    powPinOff();
    switchStatus = false;             // от клемм отключить
    swPinOff();
  break;
  }
}
