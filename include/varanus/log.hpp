/*
* 	file : log.hpp
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
* 	log.hpp : This file contains definitions for the FIFO logging system used by
* 	          Varanus.
*/

#ifndef VARANUS_LOG_HPP
#define VARANUS_LOG_HPP

// Mbed
#include <mbed.h>
#include <rtos.h>

namespace Varanus
{
	// Log : Manages and maintains a thread-safe FIFO queue of log entries
	template <typename T, size_t MAXENTRIES>
	class Log
	{
	private:
		// Track the next (next to be added) and last entry indexes
		size_t next = 0;
		size_t last = 0;
		T entries[MAXENTRIES];
		Mutex gate;

	public:
		// Find the number of entries in the queue
		size_t length()
		{
			this->gate.lock(); // Start critical section
			size_t len = (MAXENTRIES + this->next - last) % MAXENTRIES;
			this->gate.unlock(); // End critical section

			return len;
		}

		// Find the maximum volume of the queue
		size_t volume() const
		{
			return MAXENTRIES;
		}

		// Clear all entries from the queue
		void clear()
		{
			this->gate.lock(); // Start critical section

			this->next = 0;
			this->last = 0;

			this->gate.unlock(); // End critical section
		}

		// Return a specific entry by index in the queue
		T get(size_t index)
		{
			this->gate.lock(); // Start critical section
			T entry = this->entries[(this->last + index) % MAXENTRIES];
			this->gate.unlock(); // End critical section

			return entry;
		}

		// Push a new entry onto the queue
		bool push(T& entry)
		{
			bool overflow = false; // Has an overflow occured?

			this->gate.lock(); // Start critical section

			// Increment the next entry index
			this->next = (this->next + 1) % MAXENTRIES;

			// If the buffer is overflowing, increment the last entry index too
			if (this->next == this->last)
			{
				this->last = (this->last + 1) % MAXENTRIES;
				overflow = true;
			}

			// Copy the new value into the next entry index position
			this->entries[this->next] = entry;

			this->gate.unlock(); // End critical section

			return overflow;
		}

		// Remove an entry from the end of the queue. T must have a default
		// constructor
		T pop(size_t index)
		{
			this->gate.lock(); // Start critical section

			T entry;

			if (this->last != this->next)
			{
				entry = this->entries[this->last];
				this->last = (this->last + 1) % MAXENTRIES;
			}

			this->gate.unlock(); // End critical section

			return entry;
		}
	};

	// Interpret a log commands
	void log_cmd(int argc, char* argv[]);

	// Log commands
	void log_help(int argc, char* argv[]);
	void log_read(int argc, char* argv[]);
}

#endif
