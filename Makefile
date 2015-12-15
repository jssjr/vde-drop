VDE2_INCLUDE ?= /usr/local/src/vde2/include

all: drop.so

drop.so: drop.c
	$(CC) -I$(VDE2_INCLUDE) -fPIC -shared -o $@ $<

clean:
	rm -f drop.so
