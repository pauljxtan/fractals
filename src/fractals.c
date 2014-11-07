/* The fractals. */

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "fractals.h"

function_table func_table[] = {
    {"barnsley", barnsley, 2, 4},
    {"cantor", cantor, 1, 2},
    {"heighway", heighway, 2, 2},
    {"koch_curve", koch_curve, 2, 4},
    {"maple_leaf", maple_leaf, 2, 4},
    {"sierpinski", sierpinski, 2, 3}
};

char * fractal_list =
"\n"
"o Barnsley's fern [barnsley]\n"
"o Cantor set [cantor]\n"
"o Heighway's dragon [heighway]\n"
"o Koch curve [koch_curve]\n"
"o Maple leaf [maple_leaf]\n"
"o Sierpinski's triangle [sierpinski]\n"
"\n";

/********************************** FRACTALS *********************************/

double * barnsley(int n_iter) {
    int i;
    int test;
    /* All (x,y) coordinates */
    double * points = malloc(2 * n_iter * sizeof(double));

    /* Initialize at the origin */
    points[0] = 0.0;
    points[1] = 0.0;

    srand(time(NULL));

    /* Iterate */
    for (i = 2; i < (2 * n_iter); i += 2) {
        test = rand() % 100;
        if (test == 0) {
            /* Use the first transformation with 1% probability */
            points[i] = 0.0;
            points[i+1] = 0.16 * points[i-1];
        }
        else if (test < 86) {
            /* Use the second transformation with 85% probability */
            points[i] = 0.85 * points[i-2] + 0.04 * points[i-1];
            points[i+1] = -0.04 * points[i-2] + 0.85 * points[i-1] + 1.6;
        }
        else if (test < 93) {
            /* Use the third transformation with 7% probability */
            points[i] = 0.2 * points[i-2] - 0.26 * points[i-1];
            points[i+1] = 0.23 * points[i-2] + 0.22 * points[i-1] + 1.6;
        }
        else {
            /* Use the fourth transformation with 7% probability */
            points[i] = -0.15 * points[i-2] + 0.28 * points[i-1];
            points[i+1] = 0.26 * points[i-2] + 0.24 * points[i-1] + 0.44;
        }
    }
    
    return points;
}

double * cantor(int n_iter) {
    int i;
    int test;
    /* All x coordinates */
    double * points = malloc(n_iter * sizeof(double));

    /* Initialize at x=1 */
    points[0] = 1.0;

    srand(time(NULL));

    /* Iterate */
    for (i = 1; i < n_iter; i++) {
        test = rand() % 2;
        if (test) {
            /* Use the first transformation with 1/2 probability */
            points[i] = points[i-1] / 3;
        }
        else {
            /* Use the second transformation with 1/2 probability */
            points[i] = points[i-1] / 3 + 2.0 / 3;
        }
    }
    
    return points;
}

double * heighway(int n_iter) {
    int i;
    int test;
    /* All (x,y) coordinates */
    double * points = malloc(2 * n_iter * sizeof(double));

    /* Initialize at the origin */
    points[0] = 0.0;
    points[1] = 0.0;

    srand(time(NULL));

    /* Iterate (note: using non-complex version of transformations */
    for (i = 2; i < (2 * n_iter); i += 2) {
        test = rand() % 2;
        if (test) {
            /* Use the first transformation with 1/2 probability */
            points[i]   = 1/sqrt(2) * (cos(M_PI/4) * points[i-2] -
                                       sin(M_PI/4) * points[i-1]);
            points[i+1] = 1/sqrt(2) * (sin(M_PI/4) * points[i-2] +
                                       cos(M_PI/4) * points[i-1]);
        }
        else {
            /* Use the second transformation with 1/2 probability */
            points[i]   = 1/sqrt(2) * (cos(3*M_PI/4) * points[i-2] -
                                       sin(3*M_PI/4) * points[i-1]) + 1;
            points[i+1] = 1/sqrt(2) * (sin(3*M_PI/4) * points[i-2] +
                                       cos(3*M_PI/4) * points[i-1]);
        }
    }
    
    return points;
}

double * koch_curve(int n_iter) {
    int i;
    int test;
    /* All (x,y) coordinates */
    double * points = malloc(2 * n_iter * sizeof(double));

    /* Initialize at the origin */
    points[0] = 0.0;
    points[1] = 0.0;

    srand(time(NULL));

    /* Iterate */
    for (i = 2; i < (2 * n_iter); i += 2) {
        test = rand() % 4;
        if (test == 0) {
            /* Use the first transformation with 1/4 probability */
            points[i]   = 1.0/3 * points[i-2];
            points[i+1] = 1.0/3 * points[i-1];
        }
        else if (test == 1) {
            /* Use the second transformation with 1/4 probability */
            points[i]   = 1.0/6 * points[i-2] - sqrt(3)/6 * points[i-1]
                          + 1.0/3;
            points[i+1] = sqrt(3)/6 * points[i-2] + 1.0/6 * points[i-1];
        }
        else if (test == 2) {
            /* Use the third transformation with 1/4 probability */
            points[i]   = 1.0/6 * points[i-2] + sqrt(3)/6 * points[i-1] + 0.5;
            points[i+1] = - sqrt(3)/6 * points[i-2] + 1.0/6 * points[i-1]
                          + sqrt(3)/6;
        }
        else {
            /* Use the fourth transformation with 1/4 probability */
            points[i]   = 1.0/3 * points[i-2] + 2.0/3;
            points[i+1] = 1.0/3 * points[i-1];
        }
    }
    
    return points;
}

// Source: http://www.hiddendimension.com/FractalMath/IFS_Fractals_Main.html
double * maple_leaf(int n_iter) {
    int i;
    int test;
    /* All (x,y) coordinates */
    double * points = malloc(2 * n_iter * sizeof(double));

    /* Initialize at the origin */
    points[0] = 0.0;
    points[1] = 0.0;

    srand(time(NULL));

    /* Iterate */
    for (i = 2; i < (2 * n_iter); i += 2) {
        test = rand() % 100;
        if (test < 10) {
            /* Use the first transformation with 10% probability */
            points[i]   = 0.14 * points[i-2] + 0.01 * points[i-1] - 0.08;
            points[i+1] = 0.00 * points[i-2] + 0.51 * points[i-1] - 1.31;
        }
        else if (test < 45) {
            /* Use the second transformation with 35% probability */
            points[i]   =   0.43 * points[i-2] + 0.52 * points[i-1] + 1.49;
            points[i+1] = - 0.45 * points[i-2] + 0.50 * points[i-1] - 0.75;
        }
        else if (test < 80) {
            /* Use the third transformation with 35% probability */
            points[i]   = 0.45 * points[i-2] - 0.49 * points[i-1] - 1.62;
            points[i+1] = 0.47 * points[i-2] + 0.47 * points[i-1] - 0.74;
        }
        else {
            /* Use the fourth transformation with 20% probability */
            points[i]   = 0.49 * points[i-2] + 0.00 * points[i-1] + 0.02;
            points[i+1] = 0.00 * points[i-2] + 0.51 * points[i-1] + 1.62;
        }
    }
    
    return points;
}

double * sierpinski(int n_iter) {
    int i;
    int test;
    /* All (x,y) coordinates */
    double * points = malloc(2 * n_iter * sizeof(double));

    /* Initialize at the origin */
    points[0] = 0.0;
    points[1] = 0.0;

    srand(time(NULL));

    /* Iterate */
    for (i = 2; i < (2 * n_iter); i += 2) {
        test = rand() % 3;
        if (test == 0) {
            /* Use the first transformation with 1/3 probability */
            points[i]   = 0.5 * points[i-2];
            points[i+1] = 0.5 * points[i-1];
        }
        else if (test == 1) {
            /* Use the second transformation with 1/3 probability */
            points[i]   = 0.5 * points[i-2] + 0.25;
            /* Note: sqrt(0.1875) = 0.5 * sqrt(3) / 2 */
            points[i+1] = 0.5 * points[i-1] + sqrt(0.1875);
        }
        else {
            /* Use the third transformation with 1/3 probability */
            points[i]   = 0.5 * points[i-2] + 0.5;
            points[i+1] = 0.5 * points[i-1];
        }
    }
    
    return points;
}
