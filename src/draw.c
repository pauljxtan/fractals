#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "draw.h"
#include "fractals.h"
#include "ifs.h"

int main(int argc, char *argv[]) {
    char fractal[20];
    int c;
    int i, j;
    int n_iter;
    int n_dims;
    double *points;
    func_ptr func = NULL;
    int write = 0;
    char outfile[20];
    FILE *poutfile;

    /* If no arguments given, list fractals */
    if (argc < 2) {
        printf("\nImplemented fractals are:\n");
        printf("%s", fractal_list);
        print_usage();
        printf("\n");
        return EXIT_SUCCESS;
    }

    /* Parse arguments */
    opterr = 0;
    while ((c = getopt(argc, argv, "f:n:w")) != -1)
        switch (c) {
            case 'f':
                strcpy(fractal, optarg);
                break;
            case 'n':
                n_iter = atoi(optarg);
                break;
            case 'w':
                write = 1;
                break;
            /* Need to parse options for generic IFS here... */
            default:
                print_usage();
                return EXIT_FAILURE;
        }

    /* If chosen fractal is "generic", apply a generic IFS */
    if (strcmp(fractal, "generic") == 0) {
        /* Using some temporary test values for now */
        n_dims = 2;
        int n_iter = 10000;
        double init[] = {0.00, 0.00};
        int n_transforms = 4;
        int probs[] = {1, 85, 7, 7};
        double T[] = { 0.00,  0.00,  0.00,  0.16,  0.00,  0.00,
                       0.85,  0.04, -0.04,  0.85,  0.00,  1.60,
                       0.20, -0.26,  0.23,  0.22,  0.00,  1.60,
                      -0.15,  0.28,  0.26,  0.24,  0.00,  0.44};
        // points = malloc(n_dims * n_iter * sizeof(double));
        points = ifs_2d(n_iter, n_transforms, init, probs, T);
    }
    /* If chosen fractal is not "generic", look it up and draw it */
    else {
        func = lookup_func(fractal);
        n_dims = lookup_n_dims(fractal);
        //points = malloc(n_dims * n_iter * sizeof(double));
        points = func(n_iter);
    }
    
    if (write) {
        strcpy(outfile, fractal);
        strcat(outfile, ".dat");
        poutfile = fopen(outfile, "w");
    }
    
    for (i = 0; i < (n_dims * n_iter); i += n_dims)
    {
        for (j = 0; j < n_dims; j++) {
            if (write)
                fprintf(poutfile, "%f ", points[i + j]);
            else
                printf("%f ", points[i + j]);
        }
        if (write)
            fprintf(poutfile, "\n");
        else
            printf("\n");
    }

    if (write)
        fclose(poutfile);

    return EXIT_SUCCESS;
}

void print_usage() {
    printf("Usage: ./draw -f fractal -n n_iter\n");
}

func_ptr lookup_func(char *fractal) {
    function_table *ptable;

    for (ptable = func_table; ptable->fractal != NULL; ptable++) {
        if (strcmp(ptable->fractal, fractal) == 0)
            return ptable->func;
    }

    fprintf(stderr, "Invalid fractal specified\n");
    print_usage();
    exit(EXIT_FAILURE);
}

int lookup_n_dims(char *fractal) {
    function_table *ptable;

    for (ptable = func_table; ptable->fractal != NULL; ptable++) {
        if (strcmp(ptable->fractal, fractal) == 0)
            return ptable->n_dims;
    }

    fprintf(stderr, "Invalid fractal specified\n");
    print_usage();
    exit(EXIT_FAILURE);
}
