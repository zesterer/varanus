/*
* 	file : sensor.hpp
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
* 	sensor.hpp : This file contains the main sensor thread function and code
* 	           associated with reading the environmental sensor board.
*/

#ifndef VARANUS_SENSOR_HPP
#define VARANUS_SENSOR_HPP

// Varanus
#include <varanus/data.hpp>

namespace Varanus
{
	void sensor_main();
	Data sensor_sample();
}

#endif
