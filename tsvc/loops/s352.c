#include "../common.h"


int s352()
{

	clock_t start_t, end_t, clock_dif; double clock_dif_sec;

	init( "s352 ");
	start_t = clock();

    //    unrolled dot product
    TYPE dot;
    for (int nl = 0; nl < 8*ntimes; nl++) {
        dot = (TYPE)0.;
        for (int i = 0; i < LEN_1D; i += 5) {
            dot = dot + a[i] * b[i] + a[i + 1] * b[i + 1] + a[i + 2]
                * b[i + 2] + a[i + 3] * b[i + 3] + a[i + 4] * b[i + 4];
        }
        dummy(a, b, c, d, e, aa, bb, cc, dot);
    }

	end_t = clock(); clock_dif = end_t - start_t;
	clock_dif_sec = (double) (clock_dif/1000000.0);
	printf("S352 %.2f \t\t", clock_dif_sec);;
	temp = dot;
    check(-1);
	return 0;
}