/*
* 	file : shell.hpp
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
* 	out.hpp : This file contains the print() and println() definitions. This
* 	          code makes use of the argument formatting code defined in fmt.hpp.
*/

#ifndef VARANUS_OUT_HPP
#define VARANUS_OUT_HPP

// Varanus
#include <varanus/com.hpp>
#include <varanus/fmt.hpp>

namespace Varanus
{
	struct __print_ostream
	{
		static inline void write(char c)
		{
			tty.putc(c);
			if (c == '\n')
				tty.putc('\r');
			else if (c == '\r')
				tty.putc('\n');
		}
	};

	inline void print(const char* str)
	{
		__print_ostream o;
		for (size_t i = 0; str[i] != '\0'; i ++)
		{
			o.write(str[i]);
		}
	}

	template <typename... Args>
	inline void print(Args&&... args)
	{
		__print_ostream ostream;
		__pass_funct{(__fmt_arg(ostream, args), 1)...};
	}

	template <typename... Args>
	inline void println(Args&&... args)
	{
		print(args...);
		__print_ostream::write('\n');
	}
}

#endif
