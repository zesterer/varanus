/*
* 	file : data.cpp
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
* 	data.cpp : This file contains code for the environmental monitor data entry
* 	           as per declarations & definitions in <include/varanus/data.hpp>.
*/

// Varanus
#include <varanus/shell.hpp>
#include <varanus/out.hpp>

namespace Varanus
{
	Data::Data()
	{
		this->datetime = 0;
		this->temp     = 0;
		this->press    = 0;
		this->humid    = 0;
	}

	void Data::__toString(char* buff, size_t size)
	{
		snprintf(buff, size, "time = %u, temperature = %f, pressure = %f, humidity = %f", (unsigned int)this->datetime, this->temp, this->press, this->humid);
	}

	void Data::__toCSV(char* buff, size_t size)
	{
		time_t ctime = time(&this->datetime);
		tm* timeval;
		timeval = localtime(&ctime);

		snprintf(buff, size, "%u-%u-%u, %u:%u:%u, %f, %f, %f",
			timeval->tm_year + 1900, timeval->tm_mon, timeval->tm_mday,
			timeval->tm_hour, timeval->tm_min, timeval->tm_sec,
			this->temp, this->press, this->humid
		);
	}
}
