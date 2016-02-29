input="bb{AB3}.bbb(AB].cc(AB).fr{AB}.tt[AB].sf(AB)";
expected="<math><mstyle mathvariant=\"bold\"><mrow><mi>A</mi><mi>B</mi><mn>3</mn></mrow></mstyle><mo>.</mo><mstyle mathvariant=\"double-struck\"><mrow><mi>A</mi><mi>B</mi></mrow></mstyle><mo>.</mo><mstyle mathvariant=\"script\"><mrow><mi>A</mi><mi>B</mi></mrow></mstyle><mo>.</mo><mstyle mathvariant=\"fraktur\"><mrow><mi>A</mi><mi>B</mi></mrow></mstyle><mo>.</mo><mstyle mathvariant=\"monospace\"><mrow><mi>A</mi><mi>B</mi></mrow></mstyle><mo>.</mo><mstyle mathvariant=\"sans-serif\"><mrow><mi>A</mi><mi>B</mi></mrow></mstyle></math>";
output=`echo -n "$input" | build/amath`

if [[ "$output" == "$expected" ]]; then
	echo "PASS: $0"
else
	echo "FAIL: $0 (expected $expected but got $output)"
fi

