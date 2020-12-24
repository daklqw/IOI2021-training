#!/bin/bash
for ((i = 1; i <= 2; ++i)) do
	../../gens/tree > $i.in
done
for ((i = 3; i <= 5; ++i)) do
	../../gens/tree 100000 > $i.in
done
