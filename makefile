LDLIBS=$(shell $(XENOCONFIG) --skin=native --apcs/fpic --arm_linux --ldflags)
CFLAGS=-mfloat-abi=hard -mfpu=neon -g
