#!/bin/bash
for ((i = 1; i <= 3; ++i)) do
	../../gens/allrandom 300 > $i.in
done
for ((i = 4; i <= 6; ++i)) do
	../../gens/small > $i.in
done
../../gens/fulledge 300 > 7.in
