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
* 	state.hpp : This file contains the definition of the program state
* 	          for Varanus.
*
*/

#ifndef VARANUS_STATE_HPP
#define VARANUS_STATE_HPP

// Mbed
#include <mbed.h>

namespace Varanus
{
	// The program state
	class State
	{
	private:
		float sampleRate   = 15.0f;
		bool  liveLogging  = false;
		bool  loggingState = true;
		bool  halted       = false;
		Mutex gate;

	public:
		float getSampleRate();
		bool getLiveLogging();
		bool getLoggingState();
		bool getHalted();

		void setSampleRate(float sampleRate);
		void setLiveLogging(float liveLogging);
		void setLoggingState(float loggingState);
		void halt();
	};
}

#endif
