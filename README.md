fractals
========

Computing and visualizing fractals.

### Usage ###
To compute Sierpinski's triangle with 10^5 iterations:

```bash
$ draw -f sierpinski -n 10000
```
(Run with -w flag to write to file without stdout.)
(Run without arguments for list of fractals and usage.)

### Custom affine transforms (only 2D for now) ###
You can supply your own affine transforms in an input parameter file with the following format:
* Row 1: initial coordinates
* Row 2: number of transforms
* Row 3: % probability of each transform
* Remaining rows: each transform ("a b c d e f") where
```
         |a b| |x|   |e|
f(x,y) = |   | | | + | | 
         |c d| |y|   |f|
```

An example for Barnley's fern, __barnsley.in__, is provided, for which the transforms in matrix form are
```
          | 0.00  0.00| |x|   |0.00|
f1(x,y) = |           | | | + |    | 
          | 0.00  0.16| |y|   |0.00|

          | 0.85  0.04| |x|   |0.00|
f2(x,y) = |           | | | + |    | 
          |-0.04  0.85| |y|   |1.60|

          | 0.20 -0.26| |x|   |0.00|
f3(x,y) = |           | | | + |    | 
          | 0.23  0.22| |y|   |1.60|

          |-0.15  0.28| |x|   |0.00|
f4(x,y) = |           | | | + |    | 
          | 0.26  0.24| |y|   |0.44|
```
Usage:
```bash
$ draw -f generic -n 10000 -p inputs/barnsley.in
```

### Currently implemented ###
Fractal [function_name]
* Barnsley's fern [barnsley]
* Cantor middle-thirds set [cantor]
* Heighway's dragon [heighway]
* Koch curve [koch_curve]
* Maple leaf [maple_leaf]
* Sierpinski's triangle [sierpinski]
