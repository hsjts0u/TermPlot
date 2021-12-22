CXX = g++
CFLAGS = -Wall -O2

BUILDDIR = build

TPINCLUDES = -Isrc/include
TPLIB = src/lib
TPLIB := $(shell find $(TPLIB) -name '*.cpp')

CTEST_DIR = test/cpp_test
CTEST_SRC = $(shell find $(CTEST_DIR) -name '*.cpp')
CTEST_OUT = $(addprefix $(BUILDDIR)/, $(CTEST_SRC:$(CTEST_DIR)/%.cpp=%.out))

PTEST_DIR = test/python_test

.phony: all test cpp_test clean

mkdir:
	- mkdir build

all: mkdir

test: mkdir

cpp_test: mkdir $(CTEST_OUT)

$(BUILDDIR)/%.out: $(CTEST_DIR)/%.cpp
	$(CXX) $(CFLAGS) $(TPINCLUDES) $(TPLIB) $^ -o $@

clean:
	rm -rf $(BUILDDIR)

