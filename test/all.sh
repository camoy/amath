#!/bin/sh

find test/* ! -iname all.sh | xargs -n1 sh
