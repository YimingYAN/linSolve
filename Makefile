example: example.cpp cma27.h ma27d.o
	@clear
	g++ -o example -lgfortran ma27d.o example.cpp -L /usr/local/gfortran/lib
ma27d.o:
	gfortran -o ma27d.o -c ma27d.f
test:
	./example
clean:
	rm *.o
