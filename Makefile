.PHONY: final run

DAY?=1
PART?=1
INPUT?=sample.txt
CC?=gcc
OUT?=bin/main

final: INPUT=personal.txt 
final: run

build:
	$(CC) day-$(DAY)/part_$(PART).c -o ./$(OUT)

clean: 
	rm ./$(OUT)

run: build
	cat ./inputs/day-$(DAY)/$(INPUT) | ./$(OUT)

