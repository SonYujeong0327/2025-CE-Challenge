#include "../common.h"


int s491(int* __restrict__ ip)
{

	clock_t start_t, end_t, clock_dif; double clock_dif_sec;

	init( "s491 ");
	start_t = clock();

    //    indirect addressing on lhs, store in sequence
    //    scatter is required
    for (int nl = 0; nl < ntimes; nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[ip[i]] = b[i] + c[i] * d[i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

	end_t = clock(); clock_dif = end_t - start_t;
	clock_dif_sec = (double) (clock_dif/1000000.0);
	printf("S491 %.2f \t\t", clock_dif_sec);;
	check(1);
	return 0;
}