/*
* 	file : fmt.hpp
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
* 	fmt.hpp : This file provides utility code for my custom-built type-inference
* 	          print system. Please be aware that this code makes extremely heavy
* 	          use of C++14's vardic templates and so may appear nonsensical at
* 	          first. Each method is designed to expand to a valid match for each
* 	          type passed to the print(), println() or fmt() functions. As far
* 	          as I am aware - other than similar code in other projects I have
* 	          developed - this is the first occurence of vardic templates used
* 	          in this way ever.
*
*/

// Mbed
#include <mbed.h>

namespace Varanus
{
	// Default format ostream, for writing to character buffers
	struct __fmt_ostream
	{
		char* buff;
		size_t pos;
		size_t size;

		__fmt_ostream(char* buff, size_t size)
		{
			this->buff = buff;
			this->pos = 0;
			this->size = size;
		}

		inline void write(char c)
		{
			if (this->pos + 1 >= this->size)
				return;

			this->buff[this->pos] = c;
			this->pos ++;
		}
	};

	// String formatter
	template <typename T>
	void __fmt_arg(T& ostream, const char* str)
	{
		for (size_t i = 0; str[i] != '\0'; i ++)
			ostream.write(str[i]);
	}

	// Character formatter
	template <typename T>
	void __fmt_arg(T& ostream, char c)
	{
		ostream.write(c);
	}

	// Int formatter
	template <typename T>
	void __fmt_arg(T& ostream, int i)
	{
		char buff[sizeof(int) * 8 + 4];
		snprintf(buff, sizeof(buff), "%i", i);
		__fmt_arg(ostream, buff);
	}

	// Unsigned int formatter
	template <typename T>
	void __fmt_arg(T& ostream, unsigned int i)
	{
		char buff[sizeof(unsigned int) * 8 + 4];
		snprintf(buff, sizeof(buff), "%u", i);
		__fmt_arg(ostream, buff);
	}

	// Long formatter
	template <typename T>
	void __fmt_arg(T& ostream, long i)
	{
		char buff[sizeof(long) * 8 + 4];
		snprintf(buff, sizeof(buff), "%li", i);
		__fmt_arg(ostream, buff);
	}

	// Unsigned long formatter
	template <typename T>
	void __fmt_arg(T& ostream, unsigned long i)
	{
		char buff[sizeof(unsigned long) * 8 + 4];
		snprintf(buff, sizeof(buff), "%lu", i);
		__fmt_arg(ostream, buff);
	}

	// Long long formatter
	template <typename T>
	void __fmt_arg(T& ostream, long long i, int base = 10, int pad = 0)
	{
		char buff[sizeof(long long) * 8 + 4];
		snprintf(buff, sizeof(buff), "%lli", i);
		__fmt_arg(ostream, buff);
	}

	// Unsigned long long formatter
	template <typename T>
	void __fmt_arg(T& ostream, unsigned long long i, int base = 10, int pad = 0)
	{
		char buff[sizeof(unsigned long long) * 8 + 4];
		snprintf(buff, sizeof(buff), "%llu", i);
		__fmt_arg(ostream, buff);
	}

	// Boolean formatter
	template <typename T>
	void __fmt_arg(T& ostream, bool val)
	{
		char buff[6];
		strcpy(buff, val ? "true" : "false");
		__fmt_arg(ostream, buff);
	}

	// Pointer formatter
	template <typename T>
	void __fmt_arg(T& ostream, void* val)
	{
		char buff[sizeof(void*) * 8 + 4];
		snprintf(buff, sizeof(buff), "%lx", val);
		__fmt_arg(ostream, buff);
	}

	struct __pass_funct
	{
		template <typename ...T>
		inline __pass_funct(T...) {}
	};

	template <size_t SIZE, typename... Args>
	inline void fmt(char(&buff)[SIZE], Args&&... args)
	{
		// Clear the buffer
		for (size_t i = 0; i < SIZE; i ++)
			buff[i] = '\0';

		__fmt_ostream ostream(buff, SIZE);
		__pass_funct{(__fmt_arg(ostream, args), 1)...};
	}
}
