#! /bin/bash
clear
g++ -Wall -pedantic max.c -fsanitize=address -g
./a.out
rm a.out