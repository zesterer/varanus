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
		this->value = 0.0f;
	}

	void Data::__toString(char* buff, size_t size) const
	{
		snprintf(buff, size, "%f", this->value);
	}
}
