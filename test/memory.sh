#!/bin/bash

exit_status=0
cur=`dirname $0`

for file in $(ls $cur/input); do
	valgrind --error-exitcode=1 --leak-check=full cat $cur/input/$file | build/amath | echo ""
	if [ $? -eq 1 ]; then
		exit_status=1
	fi
done

exit $exit_status
