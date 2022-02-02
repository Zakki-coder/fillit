#!/bin/sh

ls -1 ./../ft*.c | sed s/\.c$// | sed s/^.*ft_// | sed '/^lst/d' | sed /freeda/d | tr [:lower:] [:upper:] > basenames

while IFS= read -r i; do
	echo "$i"
    gcc -Wall -Wextra -Werror ./master_test.c ../*.c  -I../ -D$i
	./a.out
	# gcc -g3 -o3 "$i" -o "${i%.c}.out"
done < basenames
