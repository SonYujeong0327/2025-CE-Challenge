#include "../common.h"


int s222()
{

	clock_t start_t, end_t, clock_dif; double clock_dif_sec;

	init( "s222 ");
	start_t = clock();

    //    partial loop vectorizatio recurrence in middle
    for (int nl = 0; nl < ntimes/2; nl++) {
        for (int i = 1; i < LEN_1D; i++) {
            a[i] += b[i] * c[i];
            e[i] = e[i - 1] * e[i - 1];
            a[i] -= b[i] * c[i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

	end_t = clock(); clock_dif = end_t - start_t;
	clock_dif_sec = (double) (clock_dif/1000000.0);
	printf("S222\t %.2f \t\t", clock_dif_sec);;
	check(12);
	return 0;
}