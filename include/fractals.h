#ifndef FRACTALS_H
#define FRACTALS_H

// Define the function pointer type
typedef double * (* func_ptr)(int);

// Define the function table structure; stores function pointer and other
// details about each fractal
typedef struct function_table {
    char * fractal;
    func_ptr func;
    int n_dims;
    int n_transforms;
} function_table;

extern function_table func_table[];

// Declare the list of fractals to print at runtime
extern char * fractal_list;

/********************************* FRACTALS *********************************/

/* Computes Barnsley's fern using an iterated function system */
double * barnsley(int);

/* Computes the Cantor middle-thirds set using an iterated function system */
double * cantor(int);

/* Computes Heighway's dragon using an iterated function system */
double * heighway(int);

/* Computes the Koch curve using an iterated function system */
double * koch_curve(int);

/* Computes Sierpinski's triangle using an iterated function system */
double * sierpinski(int);

#endif /* FRACTALS.H */
