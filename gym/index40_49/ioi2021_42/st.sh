#!/bin/bash
filename=OJ
while true; do
	./gen
	echo run
	time ./$filename < OJ.in
	echo ok
done
