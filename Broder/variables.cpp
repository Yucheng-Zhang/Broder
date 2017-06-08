/* Definition of basic variables */

#include "variables.h"

/* Basic Variables */

const int L = 32; /* Linear size of the lattice */
const int Ns = L * L; /* Total amount of sites of the 2d square lattice */
const int Nb = 2 * Ns; /* Total amount of bonds */

int NN[Ns][4]; /* The number of the four nearest neighbours of the site */

/* Files */

FILE *fp1, *fp2, *fp3;

errno_t err2 = fopen_s(&fp1, "broder_tree.txt", "w");

errno_t err4 = fopen_s(&fp2, "broder_covertime_16.txt", "w");

errno_t err6 = fopen_s(&fp3, "broder_size_time_16.txt", "w");
