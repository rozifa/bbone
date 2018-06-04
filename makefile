LDLIBS=$(shell $(XENOCONFIG) --skin=native --ldflags)
CFLAGS=-mfloat-abi=hard -mfpu=neon
