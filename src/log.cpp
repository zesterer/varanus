/*
* 	file : log.cpp
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
* 	log.cpp : This file contains code for the log system and command as per the
* 	          declarations and definitions in <include/varanus/sensor.hpp>.
*/

// Varanus
#include <varanus/log.hpp>
#include <varanus/com.hpp>
#include <varanus/out.hpp>

// Mbed
#include <mbed.h>

namespace Varanus
{
	// Interpret a log command
	void log_cmd(int argc, char* argv[])
	{
		if (argc <= 1)
			log_help(argc, argv);
		else
		{
			if (strcmp(argv[1], "help") == 0)
				log_help(argc, argv);
			else
			if (strcmp(argv[1], "read") == 0)
				log_read(argc, argv);
			else
			{
				println("Unrecognized sub-command '", argv[1], "'\n");
				log_help(argc, argv);
			}
		}
	}

	// Display the log command help
	void log_help(int argc, char* argv[])
	{
		print(
			"Usage: log <COMMAND> [ARGUMENTS]...\n",
			"Perform an operation upon the log.\n\n",
			"Possible sub-commands include:\n",
			"    help                     - Display this help screen\n",
			"    count                    - Find the number of log entries in memory\n"
			"    status                   - Display the most recent log status\n"
			"    read <n>                 - Display n log entries in CSV format\n",
			"    read all                 - Display all log entries in CSV format\n",
			"    delete <n>               - Delete the oldest n log entries\n",
			"    delete all               - Delete all log entries\n",
			"    setdate <dd> <mm> <yyyy> - Set the system date to yyyy-mm-dd\n",
			"    settime <hh> <mm> <ss>   - Set the system time to hh:mm:ss\n",
			"    sett <t>                 - Set the sample period to t\n",
			"    state <x>                - Set the logging state to x (1/on or 0/off)\n",
			"    logging <x>              - Enable or disable live logging (1/on or 0/off)\n"
		);
	}

	// Read logs command
	void log_read(int argc, char* argv[])
	{
		if (argc <= 2)
			println("Error: no argument specified");
		else
		if (strcmp(argv[2], "all") == 0)
		{
			for (size_t i = 0; i < log.length(); i ++)
			{
				char buff[128];
				log.get(i).toCSV(buff);
				println(buff);
			}
		}
		else
		{
			int n;
			bool result = sscanf(argv[2], "%i", &n) == 1;

			if (result)
			{
				for (size_t i = log.length() - n; i < log.length(); i ++)
				{
					char buff[128];
					log.get(i).toCSV(buff);
					println(buff);
				}
			}
		}
	}
}
