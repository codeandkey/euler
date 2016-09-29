#!/bin/bash
# generate palindromes from 0-1000000

for i in {1..999}; do
	printf "%s%s\n" "$i" "$(echo $i | rev)"
done

for (( i=1; i<100; i++ )); do
	for (( k=0; k<10; k++ )); do
		printf "%s%s%s\n" "$i" "$k" "$(echo $i | rev)"
	done
done

for (( k=0; k<10; k++ )); do
	printf "%s\n" "$k"
done
