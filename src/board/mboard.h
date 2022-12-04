#ifndef _MBOARD_H_
#define _MBOARD_H_

/*
 *
 * Версия от 06 сентября 2022г.
 */

#include "stdint.h"

  // Управление дискретными портами
void swPinOn();                 // Включение нагрузки
void swPinOff();                // Отключение нагрузки

void test1L();                // Включение (для осциллографирования)
void test1H();               // Отключение

void test2L();                // Включение (для осциллографирования)
void test2H();               // Отключение

// void test3L();                // Включение (для осциллографирования)
// void test3H();               // Отключение

void portsInit();               // Инициализация дискретных портов

void configMode(uint8_t mode);  // Конфигурация режимов

#endif  //_MBOARD_H_
