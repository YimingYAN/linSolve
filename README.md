linSolve
=====

C++ interface to MA27/MA57 from HSL Mathematical Software Library.

###Problem Type:
```
  Ax = b,
```
where A is symmetric matrix.

###How to Use
1. Add source codes of the solver you would like to use (eg, MA27) to its corresponding folder; for details see Section "Add Scource Codes".
2. In your code, add headers 

  ```#include "linSolve.h"```

  ```   #include "MA27.h" ``` (or "MA57.h" if you would like to use MA57).  
  Remember to include the path to the header files when compile.
3. Declare the object:
  ```
    linSolve<Vector_Type, Matrix_Type, Solver> theSolver(n, nz, A)
  ```
  where n is the number of rows/cols and nz is the number of non-zeros. 
  Currently the interface only accepts dynamically allocated arrays, namely
  ```
    linSolve<double*, double**, MA27> theSolver(n, nz, A)
  ```.
  See example.cpp for more details.

###Example
1. See example.cpp
1. Try ```make``` and then ```make test``` to see if it works

###Add Source Codes
1. Download ```MA27```. Go to [HSL Archive](http://www.hsl.rl.ac.uk/archive/), find MA27 and choose [source](http://www.hsl.rl.ac.uk/download/MA27/1.0.0/a/).
You will have to register first in order to get a copy of MA27.
The interface  works with MA27 version 1.0.0.
2. Copy ```ma27d.f``` to the directory ```src/MA27```.
3. Download ```MA57```. Go to [MA57](http://www.hsl.rl.ac.uk/catalogue/ma57.html), 
and click [Code Download](http://www.hsl.rl.ac.uk/download/MA57/3.9.0/). 
You will have to register first in order to get a copy of MA57.
The interface works with MA57 version 3.9.0.
4. Copy ```ddeps.f```, ```ma57d.f```, ```fakemetis.f```* to ```src/MA57```.

----

* Currently does not support Metis.
