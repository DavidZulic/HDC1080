#include "HDC1080.h"

HDC1080::HDC1080()
{
	temperatureRaw = 0;
	humidityRaw = 0;
	writeData(HDC1080_Addr::CONF, 0x10);
}

void HDC1080::readSensorData()
{
	temperatureRaw = readData(HDC1080_Addr::TEMP);
	humidityRaw = readData(HDC1080_Addr::HUM);
}

void HDC1080::writeData(uint8_t address, uint16_t value)
{
	Wire.beginTransmission(I2C_ADDR);
	Wire.write(address);
	Wire.write(value);
	Wire.endTransmission();
	delay(15); //Per datasheet
}

uint16_t HDC1080::readData(uint8_t address)
{
	Wire.beginTransmission(I2C_ADDR);
	Wire.write(address);
	Wire.endTransmission();
	delay(15); //Per datasheet
	Wire.requestFrom(I2C_ADDR, 2);

	byte msb = Wire.read();
	byte lsb = Wire.read();

	return msb << 8 | lsb;
}

//Returns temperature in C
float HDC1080::getTemperature()
{
	float t = ((float)temperatureRaw * TemperatureMultiplier) - TemperatureOffset;
	clampFloat(&t, MIN_T, MAX_T);
	return t;
}

//Returns relative humidity in %
float HDC1080::getHumidity()
{
	float h = (float)humidityRaw * HumidityMultiplier;
	clampFloat(&h, MIN_H, MAX_H);
	return h;
}

void HDC1080::clampFloat(float* value, float min, float max) {
	if (*value < min)
		*value = min;
	else if (*value > max)
		*value = max;
}