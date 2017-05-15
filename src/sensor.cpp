/*
* 	file : sensor.cpp
*
* 	This file is part of Varanus.
*
* 	Varanus is free software: you can redistribute it and/or modify it under the
* 	terms of the GNU General Public License as published by the Free Software
* 	Foundation, either version 3 of the License, or (at your option) any later
* 	version.
*
* 	Varanus is distributed in the hope that it will be useful, but WITHOUT ANY
* 	WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* 	FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
* 	details.
*
* 	You should have received a copy of the GNU General Public License along with
* 	Varanus.  If not, see <http://www.gnu.org/licenses/>.
*
* 	sensor.cpp : This file contains code for the sensor system's thread as per
* 	            declarations and definitions in <include/varanus/sensor.hpp>.
*/

// Varanus
#include <varanus/com.hpp>
#include <varanus/out.hpp>

// Mbed
#include <mbed.h>

// Environmental sensor board
#include <hts221.h>
#include <LPS25H.h>

#define USE_SIMULATOR

namespace Varanus
{
	// Indicator LED
	static DigitalOut led1(LED1);

	// Environmental sensor board I2C
	I2C i2c2(I2C_SDA, I2C_SCL);
	LPS25H barometer(i2c2, LPS25H_V_CHIP_ADDR);
	HTS221 humidity(I2C_SDA, I2C_SCL);

	// Sensors

	#ifdef USE_SIMULATOR
		// Simulated metrics
		float sim_temp  = 20.0f;
		float sim_press = 100000.0f;
		float sim_humid = 40.0f;

		// Simulator update
		void sensor_simulate();
	#endif

	// sensor_main() : The main sensor thread
	void sensor_main()
	{
		humidity.init();
		humidity.calib();

		while (true)
		{
			// Time the code to syncronise sampling
			Timer t;
			t.start();

			Data entry;

			#ifdef USE_SIMULATOR
				entry.setDatetime(time(nullptr));
				entry.setTemp(sim_temp);
				entry.setPress(sim_press);
				entry.setHumid(sim_humid);
			#else
				entry = sensor_sample();
			#endif

			log.push(entry);

			#ifdef USE_SIMULATOR
				sensor_simulate();
			#endif

			// Blink the LED
			led1 = 1;
			Thread::wait(50); // 50 ms
			led1 = 0;

			// Find the sample rate
			float sampleRate = state.getSampleRate();

			// Stop execution timer
			t.stop();

			// Read the timer and wait for the sample rate, subtracting elapsed
			Thread::wait(1000 * (sampleRate - t.read()));
		}
	}

	Data sensor_sample()
	{
		Data entry;

		float temp0, humi, temp1, pres;
		humidity.ReadTempHumi(&temp0, &humi);
		barometer.get();
		temp1 = barometer.temperature();
		pres = barometer.pressure();

		entry.setDatetime(time(nullptr));
		entry.setTemp(temp1);
		entry.setPress(pres);
		entry.setHumid(humi);

		return entry;
	}

	#ifdef USE_SIMULATOR
		void sensor_simulate()
		{
			// Update simulated metrics
			sim_temp += (rand() % 100 - 50) * 0.01f;
			sim_press += (rand() % 100 - 50) * 0.1f;
			sim_humid += (rand() % 100 - 50) * 0.01f;
		}
	#endif
}
