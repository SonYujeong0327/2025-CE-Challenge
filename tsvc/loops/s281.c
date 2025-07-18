#include "../common.h"


int s281()
{

	clock_t start_t, end_t, clock_dif; double clock_dif_sec;

	init( "s281 ");
	start_t = clock();

    //    index set splitting
    //    reverse data access
    TYPE x;
    for (int nl = 0; nl < ntimes; nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            x = a[LEN_1D-i-1] + b[i] * c[i];
            a[i] = x-(TYPE)1.0;
            b[i] = x;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

	end_t = clock(); clock_dif = end_t - start_t;
	clock_dif_sec = (double) (clock_dif/1000000.0);
	printf("S281 %.2f \t\t", clock_dif_sec);;
	check(12);
	return 0;
}