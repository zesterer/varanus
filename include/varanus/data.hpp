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

namespace Varanus
{
	class Data
	{
	private:
		float value;

	public:
		Data();

		// Not for standard use
		void __toString(char* buff, size_t size) const;


		template <size_t SIZE> void toString(char(&buff)[SIZE]) const { this->__toString(buff, SIZE); } // Templated to accept variable-size buffers. This prevents overflows
	};
}

#endif
