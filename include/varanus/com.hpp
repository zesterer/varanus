/*
* 	file : com.hpp
*
* 	Copyright 2017 Joshua Barretto
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
* 	com.hpp : This file contains common utility function and object definitions
* 	          for Varanus.
*
*/

#ifndef VARANUS_COM_HPP
#define VARANUS_COM_HPP

// Varanus
#include <varanus/log.hpp>
#include <varanus/data.hpp>

// Mbed
#include <mbed.h>

namespace Varanus
{
	// The program state
	struct State
	{
		float sampleRate = 1.0f;
		bool liveLogging = false;
		Mutex gate;

		float getSampleRate()
		{
			this->gate.lock(); // Begin critical section
			float sampleRate = this->sampleRate;
			this->gate.unlock(); // End critical section
			return sampleRate;
		}

		bool getLiveLogging()
		{
			this->gate.lock(); // Begin critical section
			float liveLogging = this->liveLogging;
			this->gate.unlock(); // End critical section
			return liveLogging;
		}

		void setSampleRate(float sampleRate)
		{
			this->gate.lock(); // Begin critical section
			this->sampleRate = sampleRate;
			this->gate.unlock(); // End critical section
		}

		void setLiveLogging(float liveLogging)
		{
			this->gate.lock(); // Begin critical section
			this->liveLogging = liveLogging;
			this->gate.unlock(); // End critical section
		}
	};

	extern Serial tty;
	extern State state;
	extern Log<Data, 256> log;

	template <typename T, typename U> T max(T a, U b) { return (a > b) ? a : b; }
	template <typename T, typename U> T min(T a, U b) { return (a > b) ? b : a; }
}

#endif
