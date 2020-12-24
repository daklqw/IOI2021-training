#!/bin/bash
../../gens/fulledge 12243 > 1.in
../../gens/fulledge 99999 > 2.in
../../gens/fulledge 100000 > 3.in
for ((i = 4; i <= 15; ++i)) do
	../../gens/allrandom > $i.in
done
for ((i = 15; i <= 30; ++i)) do
	../../gens/allrandom 100000 > $i.in
done
../../gens/hugecycle 100000 > 31.in
