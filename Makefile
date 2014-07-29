CXX=g++
FXX=gfortran

CSRC=include
FSRC27=src/MA27
FSRC57=src/MA57
FOBJ27=src/MA27
FOBJ57=src/MA57

FFLAG= -g -O2
FFLAGlib=-lgfortran -L /usr/local/gfortran/lib
mainName=example

example: $(mainName).cpp $(CSRC)/cma27.h $(CSRC)/cma57.h $(FOBJ27)/ma27d.o $(FOBJ57)/ma57d.o $(FOBJ57)/ddeps.o $(FOBJ57)/fakemetis.o
	$(CXX) -o $(mainName) $(FOBJ27)/ma27d.o $(mainName).cpp $(FFLAGlib)
$(FOBJ27)/ma27d.o:
	$(FXX) $(FFLAG) -o $(FOBJ27)/ma27d.o -c $(FSRC27)/ma27d.f
$(FOBJ57)/ma57d.o:
	$(FXX) $(FFLAG) -o $(FOBJ57)/ma57d.o -c $(FSRC57)/ma57d.f
$(FOBJ57)/ddeps.o:
	$(FXX) $(FFLAG) -o $(FOBJ57)/ddeps.o -c $(FSRC57)/ddeps.f
$(FOBJ57)/fakemetis.o:
	$(FXX) $(FFLAG) -o $(FOBJ57)/fakemetis.o -c $(FSRC57)/fakemetis.f


test:
	./$(mainName)
clean:
	rm $(FOBJ27)/*.o
	rm $(FOBJ57)/*.o
	rm $(mainName)
