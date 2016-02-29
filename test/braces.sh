#!/bin/sh

input="ubrace(1+2+3+4)_(\"4 terms\") - obrace(2+3)^(n)";
expected="<math><munder><munder><mrow><mn>1</mn><mo>+</mo><mn>2</mn><mo>+</mo><mn>3</mn><mo>+</mo><mn>4</mn></mrow><mo>&#x23DF;</mo></munder><mrow><mtext>4 terms</mtext></mrow></munder><mo>&minus;</mo><mover><mover><mrow><mn>2</mn><mo>+</mo><mn>3</mn></mrow><mo>&#x23DE;</mo></mover><mrow><mi>n</mi></mrow></mover></math>";
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]; then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi
