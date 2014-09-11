/* Generic iterated function systems. */

#include <stdlib.h>
#include <time.h>
#include "ifs.h"

// TODO:
//   generalize to accept arbitrary transformations as function arguments
//   incorporate weights for each transform
//   incorporate rotations

double * ifs_2d(int n_iter, int n_transforms, double beta [], double x0 [],
                double y0 [], double init []) {
    int i;
    int j;
    int test;
    /* All (x,y) coordinates */
    double * points = malloc(2 * n_iter * sizeof(double));

    /* Initialize at specified coordinates */
    points[0] = init[0];
    points[1] = init[1];

    srand(time(NULL));

    /* Iterate */
    for (i = 2; i < (2 * n_iter); i += 2) {
        test = rand() % n_transforms;
        /* Choose a transform and apply it */
        for (j = 0; j < n_transforms; j++) {
            if (test == j) {
                points[i]     = beta[j] * (points[i - 2] - x0[j]) + x0[j];
                points[i + 1] = beta[j] * (points[i - 1] - y0[j]) + y0[j];
                break;
            }
        }
    }

    return points;
}

