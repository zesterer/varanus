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

// Should we use the simulator?
//#define USE_SIMULATOR

namespace Varanus
{
	// Interrupt and locking things
	Ticker sampleTicker;
	Semaphore sampleSem(0);

	// Indicator LED
	static DigitalOut led1(LED1);

	// Environmental sensor board I2C
	I2C i2c2(I2C_SDA, I2C_SCL);
	LPS25H barometer(i2c2, LPS25H_V_CHIP_ADDR);
	HTS221 humidity(I2C_SDA, I2C_SCL);

	// Sensors
	Data sensor_sample();

	#ifdef USE_SIMULATOR
		// Simulated metrics
		float sim_temp  = 20.0f;
		float sim_press = 100000.0f;
		float sim_humid = 40.0f;

		// Simulator update
		void sensor_simulate();
	#endif

	// What's going on here?
	//
	// This code sets up an interrupt service routine, sensor_tick, that is
	// called whenever a sample interrupt occurs (at regular intervals). This
	// ISR operates as fast as possible and releases control of a semaphore lock
	// that triggers the main sensor thread to continue execution. Once this
	// happens, the main sensor thread will take a sample, log it, and then
	// flash the LED.
	//
	// Why is the sampling not occuring in an interrupt? Surely that would make
	// timing more precise?
	//
	// Sadly, the time() and I2C code internally makes use of mutexes. Mutexes
	// are not allowed in interrupt routines due to the risk of the software
	// becoming soft-locked.

	// Sensor tick interrupt
	void sensor_tick()
	{
		// Notify the main sensor thread that an update is required
		sampleSem.release();
	}

	// sensor_main() : The main sensor thread
	void sensor_main()
	{
		// Init and configure the environmental sensor board
		humidity.init();
		humidity.calib();

		// Find the sample rate
		float sampleRate = state.getSampleRate();

		// Initiate the sampling ticker
		sampleTicker.attach(sensor_tick, sampleRate);

		while (!state.getHalted())
		{
			// Wait for a sampling interrupt to occur
			sampleSem.wait();

			// Sample data immediately
			Data newEntry;
			#ifdef USE_SIMULATOR // Read simulation data
				newEntry.setDatetime(time(nullptr));
				newEntry.setTemp(sim_temp);
				newEntry.setPress(sim_press);
				newEntry.setHumid(sim_humid);
			#else // Read real data
				newEntry = sensor_sample();
			#endif

			// Log the new entry created by the interrupt
			if (state.getLoggingState())
				log.push(newEntry);

			// Simulate sensor data
			#ifdef USE_SIMULATOR
				sensor_simulate();
			#endif

			// Blink the LED
			led1 = 1;
			Thread::wait(50); // 50 ms
			led1 = 0;

			// Find the sample rate to check for an update
			float newRate = state.getSampleRate();
			if (newRate != sampleRate) // There's an update! Reset the interrupt
				sampleTicker.attach(sensor_tick, newRate);
			sampleRate = newRate;
		}
	}

	// Read sensor information
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

	// Perform a simulation tick
	#ifdef USE_SIMULATOR
		void sensor_simulate()
		{
			// Update simulated metrics
			sim_temp  += (rand() % 100 - 50) * 0.01f;
			sim_press += (rand() % 100 - 50) * 0.1f;
			sim_humid += (rand() % 100 - 50) * 0.01f;
		}
	#endif
}
