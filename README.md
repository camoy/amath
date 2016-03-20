`amath` is a parsing expression grammar that converts [AsciiMath] to [MathML].

[AsciiMath]: http://asciimath.org
[MathML]: https://www.w3.org/TR/MathML/

It uses [Ian Piumarta's leg parser generator][pegleg] to accomplish this.

[pegleg]: http://piumarta.com/software/peg/

	$ echo -n "x^2 + y^2 = z^2" | amath

This software is in the public domain. Where that dedication is not
recognized, redistribution and use in source and binary forms, with or
without modification, are permitted.

`amath` is maintained by Cameron Moy.
