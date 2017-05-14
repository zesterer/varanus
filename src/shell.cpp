/*
* 	file : shell.cpp
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
* 	shell.cpp : This file contains code for the Varanus shell as per the
* 	            declarations and definitions in <include/varanus/shell.hpp>.
*/

// Varanus
#include <varanus/shell.hpp>
#include <varanus/out.hpp>
#include <varanus/log.hpp>

namespace Varanus
{
	// shell_main() : The main shell thread
	void shell_main()
	{
		// Only display MOTD and info if live-logging is disabled
		if (!state.getLiveLogging())
		{
			// Shell initiation
			shell_motd(0, nullptr);
			println("Type 'help' for more information");
		}

		while (1)
		{
			// Live-log if necessary
			if (state.getLiveLogging())
				log_live();

			// Display the prompt
			print("$ ");

			// Read a line of input
			char input[128];
			shell_readline(input);

			// Parse the command into arguments
			char* argv[32];
			int argc = shell_split_args(input, argv);

			// Interpret the command arguments
			shell_cmd(argc, argv);
		}
	}

	// shell_cmd() : Interpret a command argument sequence
	void shell_cmd(int argc, char* argv[])
	{
		if (argc > 0)
		{
			if (strcmp(argv[0], "help") == 0)
				shell_help(argc, argv);
			else
			if (strcmp(argv[0], "motd") == 0)
				shell_motd(argc, argv);
			else
			if (strcmp(argv[0], "log") == 0)
				log_cmd(argc, argv);
			else
				println("Unknown command '", argv[0], '\'');
		}
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

	// __shell_split_args() : This function splits a string containing arguments
	// separated by spaces into an array of string pointers representing the
	// arguments in the string.
	int __shell_split_args(char* cmd, char** buff, size_t size)
	{
		bool in_arg = false;
		int j = 0;

		// Read characters from the command until the null terminator
		for (size_t i = 0; cmd[i] != '\0'; i ++)
		{
			// If it's whitespace, zero and skip it
			if (cmd[i] == ' ' || cmd[i] == '\t')
			{
				cmd[i] = '\0';
				in_arg = false;
			}
			else
			{
				// If it's not whitespace and we just entered a new region, assign it's location to the buffer list
				if (!in_arg)
				{
					if ((size_t)j >= size) // We've reached the buffer limit
						break;

					buff[j] = &cmd[i];
					j ++;
				}
				in_arg = true;
			}
		}

		return j;
	}

	// shell_help() : Display the shell's help
	void shell_help(int argc, char* argv[])
	{
		print(
			"Available commands:\n",
			"    help - Display this help screen\n",
			"    motd - Display the MOTD\n",
			"    log  - Execute a logging command\n",
			"    halt - Safely power down the device\n"
		);
	}

	// shell_motd() : Show the welcome 'Message Of The Day' message
	void shell_motd(int argc, char* argv[])
	{
		println("\rWelcome to Varanus ", 0, '.', 1, '.', 0, '\n');
	}
}
