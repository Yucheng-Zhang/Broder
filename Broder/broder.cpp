/* Algorithms introduced by Broder for Spanning Trees */
/* forward tree and backward tree */
/* Two dimensional square lattice */

/* To do: Add the measurement of mean cover time. Done. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rdng.h"
#include "broder.h"
#include "variables.h"

/* Calculate the N.N. with Periodic Boundary Condition */
void CalNN()
{
	for (int i = 0; i < Ns; i++) {
		NN[i][0] = (i + 1) % L + (i / L) * L; /* right */
		NN[i][1] = (i - 1 + L) % L + (i / L) * L; /* left */
		NN[i][2] = (i + L) % (L * L); /* up */
		NN[i][3] = (i - L + L * L) % (L * L); /* down */
	}
}

/* Choose the next site to walk to */
int RandomSuccessor(int u)
{
	int r = int(Random() * 4); /* four n.n. on square lattice */
	return NN[u][r];
}

/* Variables used in the algorithms */

int *FirstEntry, *LastExit; /* FirstEntry[Ns] : forward tree; LastExit[Ns] : backward tree */
static int TreeSize; /* Size of the tree */
int CoverTime; /* Number of steps costed for all the sites to be visited */
static double *TimeSize; /* Time at size [] */

/* Dynamic Memory Allocation */
void BDMA()
{
	FirstEntry = (int *)malloc(Ns * sizeof(int));
	LastExit = (int *)malloc(Ns * sizeof(int));
	TimeSize = (double *)malloc(Ns * sizeof(double));
}

/* Output the tree */
void OutputBTree(int n, int Osite)
{
	fprintf(fp1, "Tree No. %d, Start at %d\n", n + 1, Osite);
	/* output forward tree */
	fprintf(fp1, "forward tree\n");
	for (int i = 0; i < Ns; i++) {
		fprintf(fp1, "%d %d\n", i, FirstEntry[i]);
	}
	/* output backward tree */
	fprintf(fp1, "backward tree\n");
	for (int i = 0; i < Ns; i++) {
		fprintf(fp1, "%d %d\n", i, LastExit[i]);
	}
}

/* Broder Algorithms */
void Broder(int ntrees)
{
	BDMA();
	CalNN();
	for (int i = 0; i < Ns; i++) {
		TimeSize[i] = 0;
	}
	for (int k = 0; k < ntrees; k++) {
		int Osite = int(Random() * Ns); /* Start at a random site */
		/* Initialize the data */
		for (int i = 0; i < Ns; i++) {
			FirstEntry[i] = -1;
			LastExit[i] = i;
		}
		FirstEntry[Osite] = Osite;
		TreeSize = 1;
		CoverTime = 0;
		/* Random walk */
		int u = Osite, v;
		while (true) {
			if (TreeSize == Ns) break;
			v = u;
			u = RandomSuccessor(u);
			LastExit[v] = u;
			CoverTime++;
			if (FirstEntry[u] == -1) {
				FirstEntry[u] = v;
				TreeSize++;
				TimeSize[TreeSize - 1] += double(CoverTime) / ntrees;
			}
		}
		fprintf(fp2, "%d\n", CoverTime);
		/* Output trees to file */
//		OutputBTree(k, Osite);
	}
	for (int i = 0; i < Ns; i++) {
		fprintf(fp3, "%lf %d\n", TimeSize[i], i + 1);
	}
}
