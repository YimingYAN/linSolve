main=example

CXX=g++
FC=gfortran

CSRCS=$(wildcard include/*.h)
FSRC=$(sort $(dir $(wildcard src/*/)))
FOBJS=$(patsubst %.f, %.o, $(wildcard src/*/*.f))

FFLAG=-g -O2
CXXINC=-I $(shell pwd)/include
CXXFLAG=-g -O2 $(CXXINC)
BLAS=-lblas
LIBS=-lgfortran -L /usr/local/gfortran/lib $(BLAS)

example: $(main).cpp $(CSRCS) $(FOBJS)
	$(CXX) $(CXXFLAG) -o $(main) $(FOBJS) $(main).cpp $(LIBS)

$(FSRC)/%.o: $(FSRC)/%.f
	$(FC) $(FFLAG) -o $@ -c $<

test:
	./$(main)
clean:
	rm $(FOBJS)
	rm $(main)
	@rm -rf *.dSYM
