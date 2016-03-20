#!/bin/bash

input="d/dx f(x)=lim_(h->0)(f(x+h)-f(x))/h";
expected="<math><mfrac><mi>d</mi><mi>dx</mi></mfrac><mi>f</mi><mrow><mo>(</mo><mi>x</mi><mo>)</mo></mrow><mo>=</mo><munder><mo>lim</mo><mrow><mi>h</mi><mo>&rarr;</mo><mn>0</mn></mrow></munder><mfrac><mrow><mi>f</mi><mrow><mo>(</mo><mi>x</mi><mo>+</mo><mi>h</mi><mo>)</mo></mrow><mo>&minus;</mo><mi>f</mi><mrow><mo>(</mo><mi>x</mi><mo>)</mo></mrow></mrow><mi>h</mi></mfrac></math>";
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]; then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi
