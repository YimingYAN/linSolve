main=example

CXX=g++
FC=gfortran

CSRCS=$(wildcard include/*.h)
FSRC=$(sort $(dir $(wildcard src/*/)))
FOBJS=$(patsubst %.f, %.o, $(wildcard src/*/*.f))

FFLAG= -g -O2
BLAS=-lblas
LIBS=-lgfortran -L /usr/local/gfortran/lib $(BLAS)


example: $(main).cpp $(CSRCS) $(FOBJS)
	$(CXX) -o $(main) $(FOBJS) $(main).cpp $(LIBS)

$(FSRC)/%.o: $(FSRC)/%.c
	$(FC) $(FFLAG) -o $@ -c $<

test:
	./$(mainName)
clean:
	rm $(FOBJS)
	rm $(mainName)
