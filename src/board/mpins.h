#ifndef _MPINS_H_
#define _MPINS_H_
/*
* https://github.com/BLavery/SAMD21-M0-Mini
* select the board: Tools/Board = Arduino SAMD / "Arduino Zero (Native USB Port)".
* Double-click the board reset button. Upload. See if a LED blinks.
* explain a bit:
* 1. The Arduino bootloader uses double click on reset button to enter flash upload mode. Single
*    reset enters normal running mode. (Boot0/1 jumpers, like STM32 uses, are not used on the SAMD.)
* 2. The serial/bossac mode of USB upload is included in the Arduino install.
* 3. The regular user LED is missing. So we choose one of the TX/RX LEDs. For the moment, 
*    the Arduino sketch is NOT otherwise driving these as TX/RX indicators (see above), 
*    so we can re-employ them.
* 4. But what pin or GPIO number? For this board, reference the pins as 0-26 or A0-A5. Not D25, 
*    nor PB03 or PB3.
*
* https://github.com/arduino/ArduinoCore-samd/pull/374/files
* additional analog inputs: A6-A11 #374 
*
* Версия от 12 октября 2022г. 
* pcb: mcdm.v53 с исправлениями
*/

#include "stdint.h"

namespace MPins
{
//                  name        arduino_pin  M0-MINI   SAMD21_name
// A0 PA02 - аналоговый выход на цепь разряда
constexpr uint8_t dac_pin           =   14;    // A0   PA02

// A3 PA04 - плюсовой вход измерителя напряжения на нагрузке
constexpr uint8_t bat_plus_pin      =   17;    // A3   PA04
constexpr uint8_t bat_plus_mux      =    4;    // A3   PA04

// A4 PA05 - минусовой вход измерителя напряжения на нагрузке
constexpr uint8_t bat_minus_pin     =   18;    // A4   PA05
constexpr uint8_t bat_minus_mux     =    5;    // A4   PA05

// D8 PA06 - плюсовой вход измерителя тока
constexpr uint8_t shunt_plus_pin    =   46;    // D8   additional analog as PA06
constexpr uint8_t shunt_plus_mux    =    6;    // D8   additional analog as PA06

// D9 PA07 - минусовой вход измерителя тока
constexpr uint8_t shunt_minus_pin   =   47;    // D9   additional analog as PA07
constexpr uint8_t shunt_minus_mux   =    7;    // D9   additional analog as PA07

// D2 PA08 - плюсовой вход измерителя напряжения источника или температуры (резерв)
constexpr uint8_t pow_plus_pin      =   51;    // D2   additional analog as PA08
constexpr uint8_t pow_plus_mux      =    8;    // D2   additional analog as PA08

// D3 PA09 - минусовой вход измерителя напряжения источника (резерв)
constexpr uint8_t pow_minus_pin     =   50;    // D3   additional analog as PA09
constexpr uint8_t pow_minus_mux     =    9;    // D3   additional analog as PA09

// D10, D12 - Выходы компараторов COMP0 и COMP1
constexpr uint8_t ac0_pin           =   10;    // D10  alt PA18
constexpr uint8_t ac1_pin           =   12;    // D12  alt PA19



// // D0/D1 PA11/PA10 - SERCOM/UART (Serial1, обмен с ESP32)                                         Logic Analyzer Inputs v.6
// constexpr uint8_t uart_rx           =    0;    // D0   PA11/UART-RX                                       Ch 0
// constexpr uint8_t uart_tx           =    1;    // D1   PA10/UART-TX                                       Ch 1
// constexpr uint8_t sw_pin            =   13;    // D13  PA17 Управление силовыми ключами (нагрузкой)       Ch 2
//                                                //      /reset                                             Ch 3
// constexpr uint8_t test1             =    2;    // D4   PA14 Тестовый вывод для осциллографирования 1      Ch 4
// constexpr uint8_t test3             =   11;    // D11  PA16 Тестовый вывод для осциллографирования 3      Ch 5
// constexpr uint8_t test2             =   12;    // D12  PA19 Тестовый вывод для осциллографирования 2      Ch 6
// constexpr uint8_t out_pin           =   10;    // D10  PA18 ШИМ на силовой преобразователь                Ch 7

// v80
// D0/D1 PA11/PA10 - SERCOM/UART (Serial1, обмен с ESP32)                                         Logic Analyzer Inputs v80
constexpr uint8_t uart_rx           =    0;    // D0   PA11/UART-RX                                       Ch 0
constexpr uint8_t uart_tx           =    1;    // D1   PA10/UART-TX                                       Ch 1
constexpr uint8_t sw_pin            =   19;    // A5   PB02 Управление силовыми ключами (нагрузкой)       Ch 2
                                               // RST  /reset                                             Ch 3
constexpr uint8_t test1             =    2;    // D4   PA14 Тестовый вывод для осциллографирования 1      Ch 4
constexpr uint8_t ready             =   16;    // A2   PB09 Флаг синхронизации                            Ch 5
constexpr uint8_t test2             =   15;    // A1   PB08 Тестовый вывод для осциллографирования 2      Ch 6
constexpr uint8_t out_pin           =   11;    // D11  PA16 ШИМ на силовой преобразователь                Ch 7

constexpr uint8_t led_rx            =   25;    // no   PB03/LED1 (LED_BUILTIN, LED_RX)
constexpr uint8_t led_tx            =   26;    // no   PA27/LED2 (LED_TX)
};

#endif // !_MPINS_H_
