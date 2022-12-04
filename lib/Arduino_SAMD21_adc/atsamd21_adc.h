/* Blake Felt: Adds some extra functions to the ADC, such as
 * 16 bit and differential mode
 * MORO: 2020.05.04 проверено не всё
 */

#ifndef _ATSAMD21_ADC_H_
#define _ATSAMD21_ADC_H_

#include "stdint.h"

// taken from Arduino IDE, changes the pin to an input:
int pinPeripheral( uint32_t ulPin, EPioType ulPeripheral );

//uint8_t analogReadExtended(uint8_t bits);

// returns the internal pin value of the specified pin, useful
// for analogDifferentialRaw function
uint8_t internalPinValue(uint8_t pin); 

// modified from Arduino analogRead, can be used in conjunction with analogRead:
int16_t analogDifferential(uint8_t pin_pos,uint8_t pin_neg); 

// same as the above function, but no error checking, no pin types are changed, 
// and the positive and negative inputs are the raw values being input. 
// The DAC is not automatically shut off either. See datasheet page
int16_t analogDifferentialRaw(uint8_t mux_pos,uint8_t mux_neg); 

// sets the gain of the ADC. See page 868. All values defined above. 
void analogGain(uint8_t gain); 

// calibrates the bias and linearity based on the nvm register. 
// NVM register access code modified from
// https://github.com/arduino/ArduinoCore-samd/blob/master/cores/arduino/USB/samd21_host.c
// datasheet pages 32 and 882
void analogCalibrate(); 

//================== moro ==============
void analogReadConfig( uint8_t bits, uint8_t samples, uint8_t divider ); 
//void analogRefCompens( uint8_t val);
void analogRef( uint8_t ref );
//======================================

// set the analog reference voltage, but with all available options
// (the Arduino IDE neglects some). The Arduino IDE also changes
// the gain when analogReference() is used, but this won't. pg 861
void analogReference2(uint8_t ref); 

// increases accuracy of gain stage by enabling the reference buffer
// offset compensation. Takes longer to start. pg 861
void analogReferenceCompensation(uint8_t val);

// sets the ADC clock relative to the peripheral clock. pg 864
void analogPrescaler(uint8_t val);

// resets the ADC. pg 860
// note that this doesn't put back the default values set by the 
// Arduino IDE. 
void analogReset();

//============ moro ========================
// https://github.com/aswild/samd21

//==========================================

//void dacWrite10bit(const uint16_t value);




#endif //!_ATSAMD21_ADC_H_
