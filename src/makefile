CC = clang
CFLAGS = -Wall -Wextra -std=c11
LDLIBS = -lm

SOURCES = main.c setup.c DPV_setup.c CV_setup.c SqW_setup.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = my_program

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)