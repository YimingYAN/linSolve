CXX=g++
FXX=gfortran
FFLAG=-lgfortran -L /usr/local/gfortran/lib
mainName=example

example: $(mainName).cpp cma27.h ma27d.o
	$(CXX) -o $(mainName) ma27d.o $(mainName).cpp $(FFLAG)
ma27d.o:
	$(FXX) -o ma27d.o -c ma27d.f
test:
	./$(mainName)
clean:
	rm *.o
	rm $(mainName)
