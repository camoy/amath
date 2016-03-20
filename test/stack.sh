#!/bin/bash

input="stackrel\"def\"= or stackrel Delta =\" \"(\"or \":=)";
expected="<math><mover><mo>=</mo><mtext>def</mtext></mover><mo>or</mo><mover><mo>=</mo><mi>&Delta;</mo></mover><mtext> </mtext><mrow><mo>(</mo><mtext>or </mtext><mo>&Assign;</mo><mo>)</mo></mrow></math>"
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]; then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi
