/*
* 	file : shell.cpp
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
#include <varanus/out.hpp>

namespace Varanus
{
	void shell_motd()
	{
		println("\nWelcome to Varanus ", 0, '.', 1, '.', 0);
	}

	int shell_main()
	{
		// Shell initiation
		shell_motd();
		println("Type 'help' for more information");

		while (1)
		{
			char input[256];
			print("$ ");
			shell_readline(input);

			println("You wrote: ", input);
		}

		return 0;
	}

	// __shell_readline() : This function is not intended to be called by
	// ordinary code. Instead, a templated wrapper exists that prevents buffer
	// overflows by passing the size of the buffer too. This function reads text
	// from the serial I/O until a newline or EoT character is found.
	void __shell_readline(char* buff, size_t size)
	{
		size_t i;
		for (i = 0; i < size - 1; i ++)
		{
			char c = tty.getc();
			buff[i] = c;
			print(c);
			if (c == '\0' || c == '\x04' || c == '\n' || c == '\r')
				break;
		}
		buff[i] = '\0';
	}
}
