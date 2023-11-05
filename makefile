CC = gcc
DEPS = raylib.h
LIBS := 
LDFLAGS := 

ifeq ($(OS), WINDOWS_NT)
	LIBS = -llibraylib -lopengl32 -lgdi32 -lwinmm
	LDFLAGS = -L.
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		LIBS += -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
		LDFLAGS = -L/usr/local/lib
	endif
endif

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(LDFLAGS) $(LIBS)

flappybinchicken: main.o 
	$(CC) -o flappybinchicken main.o $(LDFLAGS) $(LIBS)

