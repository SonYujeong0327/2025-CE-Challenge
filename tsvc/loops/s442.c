#include "../common.h"


int s442()
{

	clock_t start_t, end_t, clock_dif; double clock_dif_sec;

	init( "s442 ");
	start_t = clock();

    //    computed goto
    for (int nl = 0; nl < ntimes/2; nl++) {
        for (int i = 0; i < LEN_1D; i++) {
            switch (indx[i]) {
                case 1:  goto L15;
                case 2:  goto L20;
                case 3:  goto L30;
                case 4:  goto L40;
            }
    L15:
            a[i] += b[i] * b[i];
            goto L50;
    L20:
            a[i] += c[i] * c[i];
            goto L50;
    L30:
            a[i] += d[i] * d[i];
            goto L50;
    L40:
            a[i] += e[i] * e[i];
    L50:
            ;
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

	end_t = clock(); clock_dif = end_t - start_t;
	clock_dif_sec = (double) (clock_dif/1000000.0);
	printf("S442 %.2f \t\t", clock_dif_sec);;
	check(1);
	return 0;
}