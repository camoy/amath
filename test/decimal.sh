#!/bin/bash

input="abc-123.45^-1.1";
expected="<math><mi>a</mi><mi>b</mi><mi>c</mi><msup><mn>-123.45</mn><mn>-1.1</mn></msup></math>";
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]; then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi
