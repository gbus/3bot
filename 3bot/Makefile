
#CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
#LIBS=-ldl $(OPTLIBS)
#PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.cc src/*.cc)
OBJECTS=$(patsubst %.cc,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.cc)
TESTS=$(patsubst %.cc,%,$(TEST_SRC))

# GB: one day I will build everything as .so
#TARGET=build/libYOUR_LIBRARY.a
#SO_TARGET=$(patsubst %.a,%.so,$(TARGET))


# The Target Build
#all: $(TARGET) $(SO_TARGET) tests
all: tests


# The Unit Tests
.PHONY: tests
#tests: CFLAGS += $(TARGET)
tests: $(TESTS) $(OBJECTS)
	g++ -o $@ $(OBJECTS) -lwiringPi



pwmlib.o : pwmlib.h
servolib.o : pwmlib.h servolib.h
sonarlib.o : sonarlib.h



#.PHONY : clean
#clean :
#     rm $(TESTS) $(OBJECTS)
