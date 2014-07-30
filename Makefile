main=example

CXX=g++
FC=gfortran

CSRCS=$(wildcard include/*.h)
FSRC=$(sort $(dir $(wildcard src/*/)))
FOBJS=$(patsubst %.f, %.o, $(wildcard src/*/*.f))

FFLAG=-g -O2
CXXFLAG=-g -O2
BLAS=-lblas
LIBS=-lgfortran -L /usr/local/gfortran/lib $(BLAS)

example: $(main).cpp $(CSRCS) $(FOBJS)
	$(CXX) $(CXXFLAG) -o $(main) $(FOBJS) $(main).cpp $(LIBS)

$(FSRC)/%.o: $(FSRC)/%.c
	$(FC) $(FFLAG) -o $@ -c $<

test:
	./$(main)
clean:
	rm $(FOBJS)
	rm $(main)
