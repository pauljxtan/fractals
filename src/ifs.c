/* Generic iterated function systems. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ifs.h"

/* TODO:
 *     incorporate rotations
 */

double * ifs_2d(int n_iter, int n_transforms, double init[], int probs[],
                double T[]) {
    int i, j;
    int test;
    int prob_used; // Used to set upper limit for probability check
    /* All (x,y) coordinates */
    double * points = malloc(2 * n_iter * sizeof(double));

    /* Initialize at specified coordinates */
    points[0] = init[0];
    points[1] = init[1];

    srand(time(NULL));

    /* Iterate */
    for (i = 2; i < (2 * n_iter); i += 2) {
        test = rand() % 100;
        prob_used = 0;

        /* Check if using first transform */
        prob_used += probs[0];
        if (test < prob_used) {
            points[i]   = T[0] * points[i-2] + T[1] * points[i-1] + T[4];
            points[i+1] = T[2] * points[i-2] + T[3] * points[i-1] + T[5];
        }

        /* Check the rest */
        for (j = 1; j < n_transforms; j++) {
            prob_used += probs[j];
            if (test < prob_used) {
                points[i]   =   T[0+j*6] * points[i-2]
                              + T[1+j*6] * points[i-1] + T[4+j*6];
                points[i+1] =   T[2+j*6] * points[i-2]
                              + T[3+j*6] * points[i-1] + T[5+j*6];
                break;
            }
        }
    }

    return points;
}

