#!/bin/bash
# Run official unit tests.

failed=0
passed=0

while read -r input; do
	read -r expected
	read -r _
	got=$(build/amath <<< "$input")
	
	if [ "$got" != "$expected" ]; then
		echo -e "\e[31m(FAIL)\e[0m $input"
		echo "expected: $expected"
		echo "got:      $got"
		exit_status=1
		failed=$((failed+1))
	else
		echo -e "\e[32m(PASS) $input"
		passed=$((passed+1))
	fi

done < test/official_tests.txt

echo "failed $failed, passed $passed"
