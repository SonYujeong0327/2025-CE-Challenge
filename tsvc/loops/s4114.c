#include "../common.h"


int s4114(int* ip, int n1)
{

	clock_t start_t, end_t, clock_dif; double clock_dif_sec;

	init( "s4114");
	start_t = clock();

    //    mix indirect addressing with variable lower and upper bounds
    //    gather is required
    int k;
    for (int nl = 0; nl < ntimes; nl++) {
        for (int i = n1-1; i < LEN_1D; i++) {
            k = ip[i];
            a[i] = b[i] + c[LEN_1D-k+1-2] * d[i];
            k += 5;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

	end_t = clock(); clock_dif = end_t - start_t;
	clock_dif_sec = (double) (clock_dif/1000000.0);
	printf("S4114 %.2f \t\t", clock_dif_sec);;
	check(1);
	return 0;
}