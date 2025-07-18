#include "../common.h"


int s332(TYPE t)
{

	clock_t start_t, end_t, clock_dif; double clock_dif_sec;

	init( "s332 ");
	start_t = clock();

    //    first value greater than threshold
    int index;
    TYPE value;
    TYPE chksum;
    for (int nl = 0; nl < ntimes; nl++) {
        index = -2;
        value = -1.;
        for (int i = 0; i < LEN_1D; i++) {
            if (a[i] > t) {
                index = i;
                value = a[i];
                goto L20;
            }
        }
    L20:
        chksum = value + (TYPE) index;
        dummy(a, b, c, d, e, aa, bb, cc, chksum);
    }

	end_t = clock(); clock_dif = end_t - start_t;
	clock_dif_sec = (double) (clock_dif/1000000.0);
	printf("S332 %.2f \t\t", clock_dif_sec);;
	temp = value;
    check(-1);
	return 0;
}