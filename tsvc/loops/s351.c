#include "../common.h"


int s351()
{

	clock_t start_t, end_t, clock_dif; double clock_dif_sec;

	init( "s351 ");
	start_t = clock();

    //    unrolled saxpy
    TYPE alpha = c[0];
    for (int nl = 0; nl < 8*ntimes; nl++) {
        for (int i = 0; i < LEN_1D; i += 5) {
            a[i] += alpha * b[i];
            a[i + 1] += alpha * b[i + 1];
            a[i + 2] += alpha * b[i + 2];
            a[i + 3] += alpha * b[i + 3];
            a[i + 4] += alpha * b[i + 4];
            dummy(a, b, c, d, e, aa, bb, cc, 0.);
        }
    }

	end_t = clock(); clock_dif = end_t - start_t;
	clock_dif_sec = (double) (clock_dif/1000000.0);
	printf("S351 %.2f \t\t", clock_dif_sec);;
	check(1);
	return 0;
}