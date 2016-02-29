#!/bin/sh

input="((a*b))/c";
expected="<math><mfrac><mrow><mrow><mo>(</mo><mi>a</mi><mo>&sdot;</mo><mi>b</mi><mo>)</mo></mrow></mrow><mi>c</mi></mfrac></math>";
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]; then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi
