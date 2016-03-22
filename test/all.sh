#!/bin/bash

find test/* ! -iname all.sh | xargs -n1 bash
