#!/bin/bash

input="hat(ab) bar(xy) ulA vec v dotx ddot y";
expected="<math><mover><mrow><mi>a</mi><mi>b</mi></mrow><mo>^</mo></mover><mover><mrow><mi>x</mi><mi>y</mi></mrow><mo>&macr;</mo></mover><munder><mi>A</mi><mo>_</mo></munder><mover><mi>v</mi><mo>&rarr;</mo></mover><mover><mi>x</mi><mo>.</mo></mover><mover><mi>y</mi><mo>..</mo></mover></math>";
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]; then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi
