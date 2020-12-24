#!/bin/bash
for ((i = 1; i <= 10; ++i)) do
	../../gens/cyclebased > $i.in
done
for ((i = 11; i <= 20; ++i)) do
	../../gens/cyclebased 100000 > $i.in
done
../../gens/hugecyclebased 100000 > 21.in
