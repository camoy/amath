#!/bin/bash

exit_status=0
cur=`dirname $0`

for file in $(ls $cur/input); do
	if ! cat $cur/input/$file | amath | cmp - $cur/output/$file --quiet; then
		echo -e "\e[31m(FAIL) $file"
		exit_status=1
	else
		echo -e "\e[32m(PASS) $file"
	fi
done

exit $exit_status