/*
* 	file : main.cpp
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
* 	main.cpp : This file contains setup code for the Varanus system including
* 	           thread, hardware and I/O initiation.
*/

// Varanus
#include <varanus/com.hpp>
#include <varanus/log.hpp>
#include <varanus/data.hpp>
#include <varanus/shell.hpp>
#include <varanus/sensor.hpp>

// Mbed
#include <mbed.h>
#include <rtos.h>

namespace Varanus
{
	// USB serial TTY
	Serial tty(USBTX, USBRX);

	// Program state
	State state;
	Log<Data, 256> log;

	// Threads
	Thread shell_thread;
	Thread sensor_thread;

	extern "C" int main()
	{
		// Start threads
		shell_thread.start(shell_main);
		sensor_thread.start(sensor_main);

		return 0;
	}
}
