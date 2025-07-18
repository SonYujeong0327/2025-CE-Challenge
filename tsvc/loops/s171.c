#include "../common.h"


int s171(int inc)
{

	clock_t start_t, end_t, clock_dif; double clock_dif_sec;

	init( "s171 ");
	start_t = clock();

    //    symbolic dependence tests
    for (int nl = 0; nl < ntimes; nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            a[i * inc] += b[i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

	end_t = clock(); clock_dif = end_t - start_t;
	clock_dif_sec = (double) (clock_dif/1000000.0);
	printf("S171\t %.2f \t\t", clock_dif_sec);;
	check(1);
	return 0;
}