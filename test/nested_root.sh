#!/bin/sh

input="sqrt sqrt root3x";
expected="<math><msqrt><msqrt><mroot><mi>x</mi><mn>3</mn></mroot></msqrt></msqrt></math>";
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]; then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi
