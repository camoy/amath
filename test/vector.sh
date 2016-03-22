#!/bin/bash

input="<<a,b>> and {:(x,y),(u,v):}";
expected="<math><mrow><mo>&lang;</mo><mi>a</mi><mo>,</mo><mi>b</mi><mo>&rang;</mo></mrow><mo>and</mo><mrow><mo></mo><mtable><mtr><mtd><mi>x</mi></mtd><mtd><mi>y</mi></mtd></mtr><mtr><mtd><mi>u</mi></mtd><mtd><mi>v</mi></mtd></mtr></mtable><mo></mo></mrow></math>";
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]; then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi
