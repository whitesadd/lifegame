all:
	gcc -g -O0 -Wall src/gameoflife.c -o gameoflife
	gcc -g -O0 -Wall -DTEST_ON src/gameoflife.c -o gameoflifetest
