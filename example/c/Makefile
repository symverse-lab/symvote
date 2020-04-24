#GOBIN = $(shell pwd)/build/bin
GOBIN = $(shell pwd)
OUT = ./example
GO ?= latest

.PHONY : example

example:
	gcc -o cvote ./main.c ../../lib/vote.so -I ../../lib
	@echo "Done building C example."
