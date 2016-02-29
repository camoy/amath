#!/bin/sh

input="a//b";
expected="<math><mi>a</mi><mo>/</mo><mi>b</mi></math>";
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]; then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi
