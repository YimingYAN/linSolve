maSolver
=====

C++ interface to MA27/MA57 from HSL Mathematical Software Library

###How to use
1. Download ```MA27```. Go to [HSL Archive](http://www.hsl.rl.ac.uk/archive/), find MA27 and choose [source](http://www.hsl.rl.ac.uk/download/MA27/1.0.0/a/).
You will have to register first in order to get a copy of MA27.
The interface  works with MA27 version 1.0.0.
2. Copy ```ma27d.f``` to the directory ```src/MA27```.
3. Download ```MA57```. Go to [MA57](http://www.hsl.rl.ac.uk/catalogue/ma57.html), 
and click [Code Download](http://www.hsl.rl.ac.uk/download/MA57/3.9.0/). 
You will have to register first in order to get a copy of MA57.
The interface works with MA57 version 3.9.0.
4. Copy ```ddeps.f```, ```ma57d.f```, ```fakemetis.f``` to ```src/MA57```
4. Try ```make``` and then ```make test``` to see if it works.
