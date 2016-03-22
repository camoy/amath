#!/bin/bash

input="(a,b]={x in RR | a < x <= b}";
expected="<math><mrow><mo>(</mo><mi>a</mi><mo>,</mo><mi>b</mi><mo>]</mo></mrow><mo>=</mo><mrow><mo>{</mo><mi>x</mi><mo>&in;</mo><mo>&Ropf;</mo><mo>|</mo><mi>a</mi><mo>&lt;</mo><mi>x</mi><mo>&leq;</mo><mi>b</mi><mo>}</mo></mrow></math>";
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]; then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi

