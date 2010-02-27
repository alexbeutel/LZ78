TARGETS=main

CC=g++

.PHONY: all clean

all: main.cpp
	g++ main.cpp -o lz78

# clean:
# 	rm -f $(TARGETS)

%: %.c
	$(CC) -o $@ $<
