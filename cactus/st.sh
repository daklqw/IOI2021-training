#!/bin/bash
while true; do
	./hugegen
	time ./std < cactus.in > cactus.out
done
