#!/bin/bash

input="int_0^1f(x)dx";
expected="<math><msubsup><mo>&int;</mo><mn>0</mn><mn>1</mn></msubsup><mi>f</mi><mrow><mo>(</mo><mi>x</mi><mo>)</mo></mrow><mi>dx</mi></math>";
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]; then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi
