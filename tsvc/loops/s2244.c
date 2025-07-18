#include "../common.h"


int s2244()
{

	clock_t start_t, end_t, clock_dif; double clock_dif_sec;

	init( "s244 ");
	start_t = clock();

    //    cycle with ture and anti dependency
    for (int nl = 0; nl < ntimes; nl++) {
        for (int i = 0; i < LEN_1D-1; i++) {
            a[i+1] = b[i] + e[i];
            a[i] = b[i] + c[i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

	end_t = clock(); clock_dif = end_t - start_t;
	clock_dif_sec = (double) (clock_dif/1000000.0);
	printf("S2244\t %.2f \t\t", clock_dif_sec);;
	check(12);
	return 0;
}