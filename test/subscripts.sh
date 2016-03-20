#!/bin/bash

input="x^2+y_1+z_12^34";
expected="<math><msup><mi>x</mi><mn>2</mn></msup><mo>+</mo><msub><mi>y</mi><mn>1</mn></msub><mo>+</mo><msubsup><mi>z</mi><mn>12</mn><mn>34</mn></msubsup></math>";
output=`echo -n "$input" | build/amath`

if [[ $output == $expected ]]; then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi
