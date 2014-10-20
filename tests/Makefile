include ../make.inc

TESTS = $(patsubst %.cpp,%.tst,$(wildcard *.cpp))

all: $(TESTS)
	@for i in $(TESTS); do ./$$i; done

%.tst: %.cpp ../lib/$(LIBNAME)
	$(CXX) $(CXXFLAGS) -o $@ $< -I../include ../lib/$(LIBNAME)

