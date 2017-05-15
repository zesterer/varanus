# Varanus

---

Varanus is an embedded environmental monitoring system created using the mbed framework for a university assignment.

## Features

Varanus implements ALL parts of the assignment specification. These can be verified by testing commands, toggling logging, reading and deleting log entries, and setting the time. Further proof is available with a look through the source code.

In addition, I have done the following:

- Used the F401RE's LED light as a logging indicator
- Build a well featured shell that includes help commands, comprehensive error messages, and argument parsing
- Downloaded and modified the LPS25H library (part of the code was not compliant with C++14, so I fixed it)
- Made the entire software 100% thread-safe and overflow-proof under all circumstances
- Added extra utility commands to ease the use of the command shell
- Included my own vardic template type-matching formatted print system (include/varanus/fmt.hpp)
- Wrote a thread-safe FIFO variable-size templated ring-buffer implementation (include/varanus/log.hpp)

## Building

__Note: If you are, for whatever reason, unable to build the project, please email me at joshua.s.barretto@gmail.com so that we can arrange a time for me to personally demonstrate the project and its successful compilation__

Building Varanus is trivial with the Mbed CLI, as per the instructions on the Mbed website. You may have to modify mbed_settings.py to alter local environment build options.

On Unix-like systems (I developed the project on Arch Linux), you may run the following to compile the project

	make build

To open the arm-none-eabi GNU debugger, you may run

	make run

This will open a GNU debugger instance. Type the following to load the binary executable onto the device (ensure that the st-util GDB server is running at the same time)

	tar extended-remote :4242
	load

The board may now run freestanding.

## Name

Varanus is named after the genus of the Monitor Lizard, a family of reptiles that includes the Komodo Dragon. They are presumed to be named for their habit of standing up on two legs in order to 'monitor' their surroundings for signs of prey.
