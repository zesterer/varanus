/*
* 	file : data.hpp
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
* 	data.hpp : This file contains the data structure representing environmental
* 	           log entries
*/

#ifndef VARANUS_DATA_HPP
#define VARANUS_DATA_HPP

// Mbed
#include <mbed.h>

namespace Varanus
{
	class Data
	{
	private:
		time_t datetime;
		float  temp;
		float  press;
		float  humid;

	public:
		Data();

		// Not for standard use
		void __toString(char* buff, size_t size);
		void __toCSV(char* buff, size_t size);

		template <size_t SIZE> void toString(char(&buff)[SIZE]) { this->__toString(buff, SIZE); } // Templated to accept variable-size buffers. This prevents overflows
		template <size_t SIZE> void toCSV(char(&buff)[SIZE]) { this->__toCSV(buff, SIZE); } // Templated to accept variable-size buffers. This prevents overflows

		// Getters
		time_t getDatetime() const { return this->datetime; }
		float  getTemp()     const { return this->temp; }
		float  getPress()    const { return this->press; }
		float  getHumid()    const { return this->humid; }

		// Setters
		void setDatetime(time_t time) { this->datetime = datetime; }
		void setTemp(float temp)      { this->temp = temp; }
		void setPress(float press)    { this->press = press; }
		void setHumid(float humid)    { this->humid = humid; }
	};
}

#endif
