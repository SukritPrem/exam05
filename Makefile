

all:
	cc json_1.c
	echo -n '{"recursion":{"recursion":"recursion"}}' | ./a.out /dev/stdin | cat -e
	echo -n '"recursion"' | ./a.out /dev/stdin | cat -e
