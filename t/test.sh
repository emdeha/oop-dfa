#!/bin/bash
cd `dirname $0`

for f in **/*.test.out
do
	./${f}
done
