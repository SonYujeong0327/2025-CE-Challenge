#include "../common.h"


int s251()
{

	clock_t start_t, end_t, clock_dif; double clock_dif_sec;

	init( "s251 ");
	start_t = clock();

    //    scalar expansion
    TYPE s;
    for (int nl = 0; nl < 4*ntimes; nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            s = b[i] + c[i] * d[i];
            a[i] = s * s;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

	end_t = clock(); clock_dif = end_t - start_t;
	clock_dif_sec = (double) (clock_dif/1000000.0);
	printf("S251\t %.2f \t\t", clock_dif_sec);;
	check(1);
	return 0;
}