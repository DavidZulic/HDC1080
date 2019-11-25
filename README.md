# HDC1080 I2C library for Arduino/PlatformIO
Minimal Arduino/PlatformIO library for HDC1080 - Low-power digital humidity and temperature sensor by TI



## Usage
Create an instance of HDC1080 class and call the readSensorData() method.
To receive the response bits, it is necessary to wait 15ms.
Afterwards call getTemperature() or getHumidity() to receive measured values.
Measured values are clamped between MIN_T/MAX_T and MIN_H/MAX_H respectively..
