#!/bin/bash
filename=cactus
while true; do
	./gen
	if ./val < $filename.in; then
		echo validate ok
	else
		echo invalid input
		exit 1
	fi
	./std < $filename.in > $filename.out
	./ha < $filename.in > $filename.usr
	head -n 1 cactus.out
	if diff $filename.out $filename.usr; then
		echo ac
	else
		echo wa
		exit 1
	fi
done
