/*
* 	file : main.cpp
*
* 	This file is part of Varanus.
*
* 	Varanus is free software: you can redistribute it and/or modify
* 	it under the terms of the GNU General Public License as published by
* 	the Free Software Foundation, either version 3 of the License, or
* 	(at your option) any later version.
*
* 	Varanus is distributed in the hope that it will be useful,
* 	but WITHOUT ANY WARRANTY; without even the implied warranty of
* 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* 	GNU General Public License for more details.
*
* 	You should have received a copy of the GNU General Public License
* 	along with Varanus.  If not, see <http://www.gnu.org/licenses/>.
*/

// Varanus
#include <varanus/shell.hpp>

// Mbed
#include <mbed.h>

namespace Varanus
{
	// USB serial connection
	Serial tty(USBTX, USBRX);

	extern "C" int main()
	{
		return shell_main();
	}
}
