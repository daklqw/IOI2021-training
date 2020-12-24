#!/bin/bash
for ((i = 1; i <= 3; ++i)) do
	../../gens/fakecactus > $i.in
done
for ((i = 4; i <= 6; ++i)) do
	../../gens/fakecactus 100000 > $i.in
done
../../gens/fakefulledge > 7.in
../../gens/hugefakecactus 100000 > 8.in
