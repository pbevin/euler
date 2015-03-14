CC = gcc
CFLAGS=-g -O2 -Wall -std=gnu99
LDLIBS = -lm -lgmp

srcs := $(wildcard eu[0-9][0-9][0-9].c)
objs := $(srcs:.c=.o)

all: euler

euler: euler.o $(objs)

clean:
	rm -f euler euler.o $(objs)
