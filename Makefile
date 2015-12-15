include vde2_config.mak

all: drop.so

drop.so: drop.c
	$(CC) -I$(VDE2_INCLUDE) -fPIC -shared -o $@ $<

clean:
	rm -f drop.so
