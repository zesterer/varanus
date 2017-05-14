/*
* 	file : shell.hpp
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
*
* 	com.hpp : This file contains common utility function and object definitions
* 	          for Varanus.
*
*/

#ifndef VARANUS_SHELL_HPP
#define VARANUS_SHELL_HPP

// Mbed
#include <mbed.h>

namespace Varanus
{
	// Not for standard use
	void __shell_readline(char* buff, size_t size);
	int __shell_split_args(char* cmd, char** buff, size_t size);

	// Shell utilities
	template <size_t SIZE> void shell_readline(char(&buff)[SIZE]) { __shell_readline(buff, SIZE); } // Templated to accept variable-size buffers. This prevents overflows
	template <size_t SIZE> int shell_split_args(char* cmd, char*(&buff)[SIZE]) { return __shell_split_args(cmd, buff, SIZE); } // Templated to accept variable-size buffers. This prevents overflows

	// Shell functions
	void shell_main();
	void shell_cmd(int argc, char* argv[]);

	// Shell commands
	void shell_motd(int argc, char* argv[]);
	void shell_help(int argc, char* argv[]);
}

#endif
