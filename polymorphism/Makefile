# Usage:
# make        # compile all binary
# make clean  # remove all binaries

.PHONY := all clean
.DEFAULT_GOAL := all 

CC = gcc
O_NAME = poly # the name of the output binary

all:
	${CC} main.c -o ${O_NAME} -Wall -Og -O1 -fsanitize=address -lm

clean:
ifneq ("${wildcard ${O_NAME}}","")
	rm ${O_NAME}
endif

