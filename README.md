# amath

`amath` is a parser which converts [AsciiMath] to [MathML]. It uses the
[greg parser generator][greg].

## Usage

The program reads AsciiMath from stdin and outputs MathML to stdout.

	echo "x^2 + y^2 = z^2" | amath

## Installing

Use `make` to build and install `amath` and the shared library `libamath`.

	make
	make install

The unit tests can also be run from `make`.

	make test

The tests can be checked for memory leaks.

	make memory

## Terms

This software is in the public domain. Where that dedication is not
recognized, redistribution and use in source and binary forms, with or
without modification, are permitted.

`amath` is maintained by Cameron Moy.

[AsciiMath]: http://asciimath.org
[MathML]: https://www.w3.org/TR/MathML
[greg]: https://github.com/ooc-lang/greg
