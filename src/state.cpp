/*
* 	file : state.cpp
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
* 	sensor.cpp : This file contains code for the program state as per the
* 	            declarations and definitions in <include/varanus/state.hpp>.
*/

// Varanus
#include <varanus/state.hpp>

namespace Varanus
{
	float State::getSampleRate()
	{
		this->gate.lock(); // Begin critical section
		float sampleRate = this->sampleRate;
		this->gate.unlock(); // End critical section
		return sampleRate;
	}

	bool State::getLiveLogging()
	{
		this->gate.lock(); // Begin critical section
		float liveLogging = this->liveLogging;
		this->gate.unlock(); // End critical section
		return liveLogging;
	}

	bool State::getLoggingState()
	{
		this->gate.lock(); // Begin critical section
		float loggingState = this->loggingState;
		this->gate.unlock(); // End critical section
		return loggingState;
	}

	bool State::getHalted()
	{
		this->gate.lock(); // Begin critical section
		bool halted = this->halted;
		this->gate.unlock(); // End critical section
		return halted;
	}

	void State::setSampleRate(float sampleRate)
	{
		this->gate.lock(); // Begin critical section
		this->sampleRate = sampleRate;
		this->gate.unlock(); // End critical section
	}

	void State::setLiveLogging(float liveLogging)
	{
		this->gate.lock(); // Begin critical section
		this->liveLogging = liveLogging;
		this->gate.unlock(); // End critical section
	}

	void State::setLoggingState(float loggingState)
	{
		this->gate.lock(); // Begin critical section
		this->loggingState = loggingState;
		this->gate.unlock(); // End critical section
	}

	void State::halt()
	{
		this->gate.lock(); // Begin critical section
		this->halted = true;
		this->gate.unlock(); // End critical section
	}
}
