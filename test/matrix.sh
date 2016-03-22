#!/bin/bash

input="[[a,b],[c,d]] ((n),(k))";
expected="<math><mrow><mo>[</mo><mtable><mtr><mtd><mi>a</mi></mtd><mtd><mi>b</mi></mtd></mtr><mtr><mtd><mi>c</mi></mtd><mtd><mi>d</mi></mtd></mtr></mtable><mo>]</mo></mrow><mrow><mo>(</mo><mtable><mtr><mtd><mi>n</mi></mtd></mtr><mtr><mtd><mi>k</mi></mtd></mtr></mtable><mo>)</mo></mrow></math>" ;
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]
then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi
