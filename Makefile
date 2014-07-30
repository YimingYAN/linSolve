CXX=g++
FC=gfortran

CSRCS=$(wildcard include/*.h)
FSRC=$(sort $(dir $(wildcard src/*/)))
FOBJS=$(patsubst %.f, %.o, $(wildcard src/*/*.f))

FFLAG= -g -O2
BLAS=-lblas
CXXlib=-lgfortran -L /usr/local/gfortran/lib $(BLAS)
mainName=example

example: $(mainName).cpp $(CSRCS) $(FOBJS)
	$(CXX) -o $(mainName) $(FOBJS) $(mainName).cpp $(CXXlib)

$(FSRC)/%.o: $(FSRC)/%.c
	$(FC) $(FFLAG) -o $@ -c $<

test:
	./$(mainName)
clean:
	rm $(FOBJS)
	rm $(mainName)
