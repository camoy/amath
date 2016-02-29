#!/bin/sh

input="a/b/c/d";
expected="<math><mfrac><mi>a</mi><mi>b</mi></mfrac><mo>/</mo><mfrac><mi>c</mi><mi>d</mi></mfrac></math>";
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]; then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi
