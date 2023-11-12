CC = gcc
LIBS := 
LDFLAGS := 

ifeq ($(OS), WINDOWS_NT)
	LIBS += -llibraylib -lopengl32 -lgdi32 -lwinmm
	LDFLAGS += -L.
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		LIBS += -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	endif
endif

flappybinchicken: main.c raylib.h
	$(CC) -o flappybinchicken main.c $(LDFLAGS) $(LIBS)


