#include <stdio.h>
#include <time.h>
#include "rdng.h"
#include "broder.h"
#include "variables.h"

int main()
{
	double TIME1, TIME2;
	int ntrees = 20000; /* The number of trees generated */
	TIME1 = 1.0*clock() / CLOCKS_PER_SEC;
	set_seed(1361287);

	/* Brober algorithm */
	printf("Broder algorithm started...\n");
	Broder(ntrees);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	printf("Broder algorithm completed.\n");
	
	TIME2 = 1.0*clock() / CLOCKS_PER_SEC;
	printf(":: The simulation costs about %lf seconds.\n", TIME2 - TIME1);
	return 0;
}
