# amath

`amath` is a parser which converts [AsciiMath] to [MathML]. It uses the
[leg parser generator][peg]. It is written so it may be ported to other
languages easily, but can certainly be used as a library itself.

## Usage

AsciiMath is read and the equivalent MathML is printed.

	echo "x^2 + y^2 = z^2" | amath

The default behavior does not output a surrounding math tag.

## Installing

Use `make` to build and install `amath` and the shared library `libamath`.

	make
	make install

The unit tests can also be run from `make`.

	make test

The tests can be checked for memory leaks.

	make memory

## Legal

This software is in the public domain. Anyone is free to use and
distribute it for any purpose.

`amath` is maintained by Cameron Moy.

[AsciiMath]: http://asciimath.org
[MathML]: https://www.w3.org/TR/MathML
[peg]: http://piumarta.com/software/peg/
