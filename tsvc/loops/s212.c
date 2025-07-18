#include "../common.h"


int s212()
{

//	statement reordering
//	dependency needing temporary

	clock_t start_t, end_t, clock_dif; double clock_dif_sec;

	init( "s212 ");
	start_t = clock();

	for (int nl = 0; nl < ntimes; nl++) {
		for (int i = 0; i < LEN-1; i++) {
			a[i] *= c[i];
			b[i] += a[i + 1] * d[i];
		}
		dummy(a, b, c, d, e, aa, bb, cc, 0.);
	}
	end_t = clock(); clock_dif = end_t - start_t;
	clock_dif_sec = (double) (clock_dif/1000000.0);
	printf("S212\t %.2f \t\t", clock_dif_sec);;
	check(12);
	return 0;
}
