CXX = g++
CFLAGS = --std=c++17 -Wall -O2
PBFLAGS = --std=c++17 -Wall -O2 -fPIC -shared

BUILDDIR = build

TP_INC = -Isrc/include
TP_LIB = src/lib
TP_LIB := $(shell find $(TP_LIB) -name '*.cpp')

PY_INC = $(shell python3-config --includes) 
PB_INC = -Iextern/pybind11/include

BINDSRC = src/_termplot_pybind.cpp

PYTERMPLOT = termplot$(shell python3-config --extension-suffix)

CTEST_DIR = test/cpp_test
CTEST_SRC = $(shell find $(CTEST_DIR) -name '*.cpp')
CTEST_OUT = $(addprefix $(BUILDDIR)/, $(CTEST_SRC:$(CTEST_DIR)/%.cpp=%.out))

PTEST_DIR = test/python_test

.phony: all test cpp_test clean

$(PYTERMPLOT): mkdir $(BINDSRC) $(TP_LIB)
	$(CXX) $(PBFLAGS) $(TP_INC) $(PB_INC) $(PY_INC) $(filter-out $<,$^) -o $(BUILDDIR)/$(PYTERMPLOT)

test: $(PYTERMPLOT)
	python3 $(PTEST_DIR)/*.py

cpp_test: mkdir $(CTEST_OUT) 
	@for x in $(CTEST_OUT); do ./$${x}; done

$(BUILDDIR)/%.out: $(CTEST_DIR)/%.cpp
	$(CXX) $(CFLAGS) $(TP_INC) $(TP_LIB) $^ -o $@

clean:
	rm -rf $(BUILDDIR)

mkdir:
	$(shell [ ! -d "build" ] && mkdir build)

