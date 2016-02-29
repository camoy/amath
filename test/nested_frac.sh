#!/bin/sh

input="(a/b)/(c/d)";
expected="<math><mfrac><mrow><mfrac><mi>a</mi><mi>b</mi></mfrac></mrow><mrow><mfrac><mi>c</mi><mi>d</mi></mfrac></mrow></mfrac></math>";
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]
then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi
