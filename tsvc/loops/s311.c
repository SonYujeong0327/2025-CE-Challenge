#include "../common.h"


int s311()
{

	clock_t start_t, end_t, clock_dif; double clock_dif_sec;

	init( "s311 ");
	start_t = clock();

    //    sum reduction
    TYPE sum;
    for (int nl = 0; nl < ntimes*10; nl++) {
        sum = (TYPE)0.;
        for (int i = 0; i < LEN_1D; i++) {
            sum += a[i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, sum);
    }

	end_t = clock(); clock_dif = end_t - start_t;
	clock_dif_sec = (double) (clock_dif/1000000.0);
	printf("S311 %.2f \t\t", clock_dif_sec);;
	check(1);
	return 0;
}