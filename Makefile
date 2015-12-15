include vde2_config.mak

all: drop_all.so

drop_all.so: drop_all.c
	$(CC) -I$(VDE2_INCLUDE) -fPIC -shared -o $@ $<

clean:
	rm -f drop_all.so
