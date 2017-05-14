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
#include <x_nucleo_iks01a1.h>

namespace Varanus
{
	// Indicator LED
	static DigitalOut led1(LED1);

	// Environmental expansion board
	static X_NUCLEO_IKS01A1* exp_board = X_NUCLEO_IKS01A1::Instance(D14, D15);

	// Sensors

	// sensor_main() : The main sensor thread
	void sensor_main()
	{
		while (true)
		{
			led1 = 1;
			wait(0.2);
			led1 = 0;
			wait(0.8);

			Data entry;

			entry.setTime(0);
			entry.setTemp(0);
			entry.setPress(0);
			entry.setHumid(0);

			log.push(entry);
		}
	}
}
