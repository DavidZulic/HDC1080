/*
HDC1080 - Low-power digital humidity and temperature sensor by TI
Arduino/PlatformIO library

Usage:
Create an instance of HDC1080 class and call the readSensorData() method.
To receive the response bits, it is necessary to wait 15ms.
Afterwards call getTemperature() or getHumidity() to receive measured values.
Measured values are clamped between MIN_T/MAX_T and MIN_H/MAX_H respectively..
*/

#ifndef HDC1080_H
#define HDC1080_H

#include <Arduino.h>
#include <Wire.h>

#define I2C_ADDR 0x40			//I2C address (FIXED)
#define HDC1080_MAX_F 400000	//Max I2C frequency

#define MIN_T -20	//Min. temperature
#define MAX_T 80	//Max. temperature
#define MIN_H 0		//Min. relative humidity
#define MAX_H 100	//Max. relative humidity

typedef enum {
	TEMP = 0x00,
	HUM = 0x01,
	CONF = 0x02
} HDC1080_Addr;		

class HDC1080 {
public:
	HDC1080();

	void readSensorData();
	float getTemperature();
	float getHumidity();

private:
	const double HumidityMultiplier = 0.0015258789; // =100.0/65536.0
	const double TemperatureMultiplier = 0.00251770019; // =165.0/65536.0
	const float TemperatureOffset = 40.0f;

	uint16_t temperatureRaw;
	uint16_t humidityRaw;

	void writeData(uint8_t address, uint16_t value);
	uint16_t readData(uint8_t address);
	void clampFloat(float* value, float min, float max);
};
#endif