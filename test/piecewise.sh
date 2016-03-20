#!/bin/bash

input="x/x={(1,if x!=0),(\"undefined\",if x=0):}";
expected="<math><mfrac><mi>x</mi><mi>x</mi></mfrac><mo>=</mo><mrow><mo>{</mo><mtable><mtr><mtd><mn>1</mn></mtd><mtd><mo>if</mo><mi>x</mi><mo>&NotEqual;</mo><mn>0</mn></mtd></mtr><mtr><mtd><mtext>undefined</mtext></mtd><mtd><mo>if</mo><mi>x</mi><mo>=</mo><mn>0</mn></mtd></mtr></mtable><mo></mo></mrow></math>";
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]
then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi
