CXX=g++
FXX=gfortran
mainName=example

example: $(mainName).cpp cma27.h ma27d.o
	$(CXX) -o $(mainName) -lgfortran ma27d.o $(mainName).cpp -L /usr/local/gfortran/lib
ma27d.o:
	$(FXX) -o ma27d.o -c ma27d.f
test:
	./$(mainName)
clean:
	rm *.o
	rm $(mainName)
