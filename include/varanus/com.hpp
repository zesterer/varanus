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
#include <varanus/state.hpp>
#include <varanus/log.hpp>
#include <varanus/data.hpp>

// Mbed
#include <mbed.h>

namespace Varanus
{
	extern Serial tty;
	extern State state;
	extern Log<Data, 256> log;

	template <typename T, typename U> T max(T a, U b) { return (a > b) ? a : b; }
	template <typename T, typename U> T min(T a, U b) { return (a > b) ? b : a; }
}

#endif
