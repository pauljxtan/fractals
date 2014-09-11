#ifndef DRAW_H
#define DRAW_H

#include "fractals.h"

void print_usage();

func_ptr lookup_func(char *);
int lookup_n_dims(char *);

#endif /* DRAW_H */
