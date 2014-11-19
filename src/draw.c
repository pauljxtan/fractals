#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "draw.h"
#include "fractals.h"
#include "ifs.h"

int main(int argc, char *argv[]) {
    char fractal[32];
    char infile[64];
    char outfile[32];
    int c;
    int i, j;
    int n_dims;
    int n_iter;
    int write = 0;
    double *points;
    FILE *poutfile;
    func_ptr func = NULL;

    /* If no arguments given, list fractals */
    if (argc < 2) {
        printf("\nPre-defined fractals are:\n");
        printf("%s", fractal_list);
        print_usage();
        printf("\n");
        return EXIT_SUCCESS;
    }

    /* Parse arguments */
    opterr = 0;
    while ((c = getopt(argc, argv, "f:n:wp:")) != -1)
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
            case 'p':
                strcpy(infile, optarg);
                break;
            default:
                print_usage();
                return EXIT_FAILURE;
        }

    /* If chosen fractal is "generic2d", apply a generic 2D IFS */
    /* TODO: Generalize for any dimension later */
    if (strcmp(fractal, "generic2d") == 0) {
        n_dims = 2;

        /* Parse the parameter file */
        FILE *pinfile = fopen(infile, "r");
        
        /* Initial coordinates */
        double init[n_dims];
        fscanf(pinfile, "%lf %lf", &init[0], &init[1]);
        
        /* Number of affine tranformations */
        int n_transforms;
        fscanf(pinfile, "%d", &n_transforms);
        
        /* Probability for each transformation */
        int * probs = (int *) malloc(n_transforms * sizeof(int));
        for (i = 0; i < n_transforms; i++)
            fscanf(pinfile, "%d", &probs[i]);
        
        /* Transformation coefficients */
        double * T = (double *) malloc(6 * n_transforms * sizeof(double));
        for (i = 0; i < 6 * n_transforms; i++)
            fscanf(pinfile, "%lf", &T[i]);
        
        fclose(pinfile);

        /* Compute the fractal */
        points = ifs_2d(n_iter, n_transforms, init, probs, T);
    }
    
    /* If chosen fractal is not "generic2d", look it up and draw it */
    else {
        func = lookup_func(fractal);
        n_dims = lookup_n_dims(fractal);
        points = func(n_iter);
    }
    
    if (write) {
        strcpy(outfile, fractal);
        strcat(outfile, ".dat");
        poutfile = fopen(outfile, "w");
    }
    
    for (i = 0; i < (n_dims * n_iter); i += n_dims) {
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
    printf("Usage:\n");
    printf("    draw -f fractal -n n_iter\n");
    printf("OR\n");
    printf("    draw -f generic2d -n n_iter -p file\n");
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
