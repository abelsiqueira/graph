include ../make.inc

OBJS = $(patsubst ../src/%.cpp,%.o,$(wildcard ../src/*.cpp))

%.o: ../src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I../include

all lib: $(LIBNAME)

$(LIBNAME): $(OBJS)
	$(AR) $(LIBNAME) $(OBJS)

clean purge:
	rm -f $(OBJS) $(LIBNAME)
