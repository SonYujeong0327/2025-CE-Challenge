#include "../common.h"


int s231()
{

	clock_t start_t, end_t, clock_dif; double clock_dif_sec;

	init( "s231 ");
	start_t = clock();

    //    loop with data dependency
    for (int nl = 0; nl < 100*(ntimes/LEN_2D); nl++) {
        for (int i = 0; i < LEN_2D; ++i) {
            for (int j = 1; j < LEN_2D; j++) {
                aa[j][i] = aa[j - 1][i] + bb[j][i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

	end_t = clock(); clock_dif = end_t - start_t;
	clock_dif_sec = (double) (clock_dif/1000000.0);
	printf("S231\t %.2f \t\t", clock_dif_sec);;
	check(11);
	return 0;
}