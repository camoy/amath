#!/bin/bash

input="sin^-1(x)";
expected="<math><msup><mo>sin</mo><mn>-1</mn></msup><mrow><mo>(</mo><mi>x</mi><mo>)</mo></mrow></math>";
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]; then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi
