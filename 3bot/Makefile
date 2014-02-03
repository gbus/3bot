
#CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)

CC=g++
CFLAGS=-c -Wall
#LIBS=-ldl $(OPTLIBS)
#PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.cc src/*.cc)
OBJECTS=$(patsubst %.cc,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.cc)
TESTS=$(patsubst %.cc,%,$(TEST_SRC))

TEST_OBJ=$(patsubst %.cc,%.o,$(TEST_SRC))

# GB: one day I will build everything as .so
#TARGET=build/libYOUR_LIBRARY.a
#SO_TARGET=$(patsubst %.a,%.so,$(TARGET))


# The Target Build
#all: $(TARGET) $(SO_TARGET) tests
all: $(SOURCES) $(TESTS)


# The Unit Tests
#.PHONY: tests
#tests: CFLAGS += $(TARGET)
#tests: $(OBJECTS)
#	$(CC) -o $@ $(OBJECTS) -lwiringPi

$(TESTS): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) -lwiringPi



.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY : clean
clean :
	rm $(TESTS) $(OBJECTS)
