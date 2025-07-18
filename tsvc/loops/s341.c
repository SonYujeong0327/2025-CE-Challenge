#include "../common.h"


int s341()
{

	clock_t start_t, end_t, clock_dif; double clock_dif_sec;

	init( "s341 ");
	start_t = clock();

    //    pack positive values
    //    not vectorizable, value of j in unknown at each iteration
    int j;
    for (int nl = 0; nl < ntimes; nl++) {
        j = -1;
        for (int i = 0; i < LEN_1D; i++) {
            if (b[i] > (TYPE)0.) {
                j++;
                a[j] = b[i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

	end_t = clock(); clock_dif = end_t - start_t;
	clock_dif_sec = (double) (clock_dif/1000000.0);
	printf("S341 %.2f \t\t", clock_dif_sec);;
	check(1);
	return 0;
}