#!/bin/sh

input="color(red)(x^2)+3x+color(green)(4)";
expected="<math><mstyle mathcolor=\"red\"><mrow><msup><mi>x</mi><mn>2</mn></msup></mrow></mstyle><mo>+</mo><mn>3</mn><mi>x</mi><mo>+</mo><mstyle mathcolor=\"green\"><mrow><mn>4</mn></mrow></mstyle></math>";
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]; then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi
