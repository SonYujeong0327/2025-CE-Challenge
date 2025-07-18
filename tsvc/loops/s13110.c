#include "../common.h"


int s13110()
{

	clock_t start_t, end_t, clock_dif; double clock_dif_sec;

	init( "s3110");
	start_t = clock();

    //    if to max with index reductio 2 dimensions
    int xindex, yindex;
    TYPE max, chksum;
    for (int nl = 0; nl < 100*(ntimes/(LEN_2D)); nl++) {
        max = aa[(0)][0];
        xindex = 0;
        yindex = 0;
        for (int i = 0; i < LEN_2D; i++) {
            for (int j = 0; j < LEN_2D; j++) {
                if (aa[i][j] > max) {
                    max = aa[i][j];
                    xindex = i;
                    yindex = j;
                }
            }
        }
        chksum = max + (TYPE) xindex + (TYPE) yindex;
        dummy(a, b, c, d, e, aa, bb, cc, chksum);
    }

	end_t = clock(); clock_dif = end_t - start_t;
	clock_dif_sec = (double) (clock_dif/1000000.0);
	printf("S13110\t %.2f \t\t", clock_dif_sec);;
    temp = max + xindex + 1 + yindex + 1;
	check(-1);
	return 0;
}