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
			if (strcmp(argv[1], "count") == 0)
				log_count(argc, argv);
			else
			if (strcmp(argv[1], "status") == 0)
				log_status(argc, argv);
			else
			if (strcmp(argv[1], "read") == 0)
				log_read(argc, argv);
			else
			if (strcmp(argv[1], "delete") == 0)
				log_delete(argc, argv);
			else
			if (strcmp(argv[1], "setdate") == 0)
				log_setdate(argc, argv);
			else
			if (strcmp(argv[1], "settime") == 0)
				log_settime(argc, argv);
			else
			if (strcmp(argv[1], "sett") == 0)
				log_sett(argc, argv);
			else
			if (strcmp(argv[1], "state") == 0)
				log_state(argc, argv);
			else
			if (strcmp(argv[1], "logging") == 0)
				log_logging(argc, argv);
			else
			{
				println("Unrecognized sub-command '", argv[1], "'.\n");
				log_help(argc, argv);
			}
		}
	}

	// Log incoming data live
	void log_live()
	{
		if (!state.getLoggingState())
			return;

		// Count total entries ever logged
		size_t log_count = log.count();
		while (true)
		{
			// Wait for half the sample rate or 1 second (to prevent sample misses)
			float wait_time = min(state.getSampleRate() / 2.0f, 1.0f);
			Thread::wait(1000 * wait_time);

			size_t ncount = log.count();
			if (ncount != log_count) // Display the current entry
			{
				char buff[128];
				log.get(log.length() - 1).toCSV(buff);
				println(buff);
			}
			log_count = ncount;

			// If a character is sent, exit the live log
			if (tty.readable())
			{
				tty.getc();
				break;
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
			"    status                   - Display the most recent log and status\n"
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

	// Find the number of log entries in memory
	void log_count(int argc, char* argv[])
	{
		println("The log currently contains ", log.length(), " entries.");
	}

	// Display the most recent log status
	void log_status(int argc, char* argv[])
	{
		char buff[128];
		log.get(log.length() - 1).toCSV(buff);
		println(buff);
		println("Sampling rate is set to ", state.getSampleRate(), '.');
	}

	// Read logs command
	void log_read(int argc, char* argv[])
	{
		if (argc <= 2)
			println("Error: no argument specified.");
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
			size_t n;
			bool result = sscanf(argv[2], "%u", &n) == 1;
			n = max(0, min(log.length(), n));

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

	// Delete logs command
	void log_delete(int argc, char* argv[])
	{
		if (argc <= 2)
			println("Error: no argument specified.");
		else
		if (strcmp(argv[2], "all") == 0)
		{
			println(log.length(), " log entries deleted.");
			log.clear();
		}
		else
		{
			size_t n;
			bool result = sscanf(argv[2], "%u", &n) == 1;
			n = max(0, min(log.length(), n));

			if (result)
			{
				for (size_t i = 0; i < n; i ++)
					log.pop();
				println(n, " log entries deleted.");
			}
		}
	}

	// Set the system date
	void log_setdate(int argc, char* argv[])
	{
		if (argc != 5)
			println("Error: Incorrect number of arguments.");
		else
		{
			bool result = true;

			int day, month, year;
			result &= sscanf(argv[2], "%u", &day) == 1;
			result &= sscanf(argv[3], "%u", &month) == 1;
			result &= sscanf(argv[4], "%u", &year) == 1;

			if (!result)
				println("Error: Invalid argument(s).");
			else
			{
				time_t ctime = time(nullptr);
				tm* timeval;
				timeval = localtime(&ctime);

				// Update the date values
				timeval->tm_mday = day;
				timeval->tm_mon  = month;
				timeval->tm_year = year - 1900;

				// Set the time to the new value
				set_time(mktime(timeval));
			}
		}
	}

	// Set the system time
	void log_settime(int argc, char* argv[])
	{
		if (argc != 5)
			println("Error: Incorrect number of arguments.");
		else
		{
			bool result = true;

			int hour, min, sec;
			result &= sscanf(argv[2], "%u", &hour) == 1;
			result &= sscanf(argv[3], "%u", &min) == 1;
			result &= sscanf(argv[4], "%u", &sec) == 1;

			if (!result)
				println("Error: Invalid argument(s).");
			else
			{
				time_t ctime = time(nullptr);
				tm* timeval;
				timeval = localtime(&ctime);

				// Update the time values
				timeval->tm_hour = hour;
				timeval->tm_min  = min;
				timeval->tm_sec  = sec;

				// Set the time to the new value
				set_time(mktime(timeval));
			}
		}
	}

	// Set the sample rate
	void log_sett(int argc, char* argv[])
	{
		if (argc <= 2)
			println("Error: no argument specified.");
		else
		{
			float rate;
			bool result = sscanf(argv[2], "%f", &rate) == 1;
			rate = min(60.0f, max(0.1f, rate));

			if (result)
			{
				state.setSampleRate(rate);
				println("Sample rate set to ", rate, '.');
			}
			else
				println("Error: unrecognized argument '", argv[2], '\'');
		}
	}

	// Toggle logging state
	void log_state(int argc, char* argv[])
	{
		if (argc <= 2)
			println("Error: no argument specified.");
		else
		if (strcmp(argv[2], "1") == 0 || strcmp(argv[2], "on") == 0)
		{
			state.setLoggingState(true);
			println("Logging enabled.");
		}
		else
		if (strcmp(argv[2], "0") == 0 || strcmp(argv[2], "off") == 0)
		{
			state.setLoggingState(false);
			println("Logging disabled.");
		}
		else
			println("Error: unrecognized argument '", argv[2], '\'');
	}

	// Toggle logging
	void log_logging(int argc, char* argv[])
	{
		if (argc <= 2)
			println("Error: no argument specified.");
		else
		if (strcmp(argv[2], "1") == 0 || strcmp(argv[2], "on") == 0)
		{
			state.setLiveLogging(true);
			println("Live logging enabled, press any key to return to shell.");
		}
		else
		if (strcmp(argv[2], "0") == 0 || strcmp(argv[2], "off") == 0)
		{
			state.setLiveLogging(false);
			println("Live logging disabled.");
		}
		else
			println("Error: unrecognized argument '", argv[2], '\'');
	}
}
