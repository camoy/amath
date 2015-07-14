# amath

`amath` is an AsciiMath to MathML parser written in C. It is free software under the ISC license.

## Building

	make

This will create a `build` directory which contains the binary, shared library, and object files. If you wish to modify the lexer or parser, you will need to install [re2c](http://re2c.org/) or [lemon](http://www.hwaci.com/sw/lemon/) respectively.

	make install

This will install to `/usr/local/` as usual.

## Usage

`amath` will reads AsciiMath input from `stdin` and prints out the equivalent MathML.

	echo "x+y" | amath
	# <mi>x</mi><mo>+</mo><mi>y</mi>
