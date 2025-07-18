#define ntimes_default 200000
#define digits_default 6

#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <sys/param.h>
#include <sys/times.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <assert.h>

// static int ntimes = ntimes_default;
int ntimes = ntimes_default;
static int digits = digits_default;

#include "types.h"
#include "dummy.inc"

#ifndef TESTS
#define TESTS 0xFFFFFFFF
#endif

// #define lll LEN

/*
 * Disable timing in the output so that we can use the output for correctness testing.
 */
#ifndef USE_CLOCK
#define clock() 0
#endif

__attribute__ ((aligned(ALIGNMENT))) X_TYPE X[lll],Y[lll],Z[lll],U[lll],V[lll];


//TYPE* __restrict__ array;
TYPE array[LEN2*LEN2] __attribute__((aligned(ALIGNMENT)));

TYPE x[LEN] __attribute__((aligned(ALIGNMENT)));
TYPE temp;
int temp_int;

// We place all of the data into one single global structure so that we can
// control its exact layout. Otherwise, the performance of the code can become
// very dependent on the exact addresses assigned to arrays at compile time, and
// probing that behavior is not the purpose of this set of benchmarks.
//
// We insert prime-multiple padding in between each array to help ensure that
// the relative offsets of the arrays are unlikely to trigger unmodelled
// architecture specific problems w.r.t. cache behavior or other CPU
// features. For example, this ensures that no two of the arrays will be
// 4K-aliased with each other, which can be important for some Intel processors.
struct GlobalData {
  __attribute__((aligned(ALIGNMENT))) TYPE a[LEN];
  int pad1[3];
  __attribute__((aligned(ALIGNMENT))) TYPE b[LEN];
  int pad2[5];
  __attribute__((aligned(ALIGNMENT))) TYPE c[LEN];
  int pad3[7];
  __attribute__((aligned(ALIGNMENT))) TYPE d[LEN];
  int pad4[11];
  __attribute__((aligned(ALIGNMENT))) TYPE e[LEN];

  int pad5[13];
  __attribute__((aligned(ALIGNMENT))) TYPE aa[LEN2][LEN2];
  int pad6[17];
  __attribute__((aligned(ALIGNMENT))) TYPE bb[LEN2][LEN2];
  int pad7[19];
  __attribute__((aligned(ALIGNMENT))) TYPE cc[LEN2][LEN2];
  int pad8[23];
  __attribute__((aligned(ALIGNMENT))) TYPE tt[LEN2][LEN2];
} global_data;

__attribute__((aligned(ALIGNMENT))) TYPE * const a = global_data.a;
__attribute__((aligned(ALIGNMENT))) TYPE * const b = global_data.b;
__attribute__((aligned(ALIGNMENT))) TYPE * const c = global_data.c;
__attribute__((aligned(ALIGNMENT))) TYPE * const d = global_data.d;
__attribute__((aligned(ALIGNMENT))) TYPE * const e = global_data.e;
__attribute__((aligned(ALIGNMENT))) TYPE (* const aa)[LEN2] = global_data.aa;
__attribute__((aligned(ALIGNMENT))) TYPE (* const bb)[LEN2] = global_data.bb;
__attribute__((aligned(ALIGNMENT))) TYPE (* const cc)[LEN2] = global_data.cc;
__attribute__((aligned(ALIGNMENT))) TYPE (* const tt)[LEN2] = global_data.tt;

int indx[LEN] __attribute__((aligned(ALIGNMENT)));


TYPE* __restrict__ xx;
TYPE* yy;

// int dummy(TYPE[LEN], TYPE[LEN], TYPE[LEN], TYPE[LEN], TYPE[LEN], TYPE[LEN2][LEN2], TYPE[LEN2][LEN2], TYPE[LEN2][LEN2], TYPE);

// int dummy_media(short[], char[], int);

int set1d(TYPE arr[LEN], TYPE value, int stride)
{
	if (stride == -1) {
		for (int i = 0; i < LEN; i++) {
			arr[i] = 1. / (TYPE) (i+1);
		}
	} else if (stride == -2) {
		for (int i = 0; i < LEN; i++) {
			arr[i] = 1. / (TYPE) ((i+1) * (i+1));
		}
	} else {
		for (int i = 0; i < LEN; i += stride) {
			arr[i] = value;
		}
	}
	return 0;
}

int set1ds(int _n, TYPE arr[LEN], TYPE value, int stride)
{
	if (stride == -1) {
		for (int i = 0; i < LEN; i++) {
			arr[i] = 1. / (TYPE) (i+1);
		}
	} else if (stride == -2) {
		for (int i = 0; i < LEN; i++) {
			arr[i] = 1. / (TYPE) ((i+1) * (i+1));
		}
	} else {
		for (int i = 0; i < LEN; i += stride) {
			arr[i] = value;
		}
	}
	return 0;
}

int set2d(TYPE arr[LEN2][LEN2], TYPE value, int stride)
{

//  -- initialize two-dimensional arraysft

	if (stride == -1) {
		for (int i = 0; i < LEN2; i++) {
			for (int j = 0; j < LEN2; j++) {
				arr[i][j] = 1. / (TYPE) (i+1);
			}
		}
	} else if (stride == -2) {
		for (int i = 0; i < LEN2; i++) {
			for (int j = 0; j < LEN2; j++) {
				arr[i][j] = 1. / (TYPE) ((i+1) * (i+1));
			}
		}
	} else {
		for (int i = 0; i < LEN2; i++) {
			for (int j = 0; j < LEN2; j += stride) {
				arr[i][j] = value;
			}
		}
	}
	return 0;
}

TYPE sum1d(TYPE arr[LEN]){
	TYPE ret = 0.;
	for (int i = 0; i < LEN; i++)
		ret += arr[i];
	return ret;
}

static inline int s471s(void)
{
// --  dummy subroutine call made in s471
	return 0;
}

static inline TYPE f(TYPE a, TYPE b){
	return a*b;
}

void check(int name){

	TYPE suma = 0;
	TYPE sumb = 0;
	TYPE sumc = 0;
	TYPE sumd = 0;
	TYPE sume = 0;
	for (int i = 0; i < LEN; i++){
		suma += a[i];
		sumb += b[i];
		sumc += c[i];
		sumd += d[i];
		sume += e[i];
	}
	TYPE sumaa = 0;
	TYPE sumbb = 0;
	TYPE sumcc = 0;
	for (int i = 0; i < LEN2; i++){
		for (int j = 0; j < LEN2; j++){
			sumaa += aa[i][j];
			sumbb += bb[i][j];
			sumcc += cc[i][j];

		}
	}
	TYPE sumarray = 0;
	for (int i = 0; i < LEN2*LEN2; i++){
		sumarray += array[i];
	}

	if (name == 1) printf("%.*G \n",digits,suma);
	if (name == 2) printf("%.*G \n",digits,sumb);
	if (name == 3) printf("%.*G \n",digits,sumc);
	if (name == 4) printf("%.*G \n",digits,sumd);
	if (name == 5) printf("%.*G \n",digits,sume);
	if (name == 11) printf("%.*G \n",digits,sumaa);
	if (name == 22) printf("%.*G \n",digits,sumbb);
	if (name == 33) printf("%.*G \n",digits,sumcc);
	if (name == 0) printf("%.*G \n",digits,sumarray);
	if (name == 12) printf("%.*G \n",digits,suma+sumb);
	if (name == 25) printf("%.*G \n",digits,sumb+sume);
	if (name == 13) printf("%.*G \n",digits,suma+sumc);
	if (name == 123) printf("%.*G \n",digits,suma+sumb+sumc);
	if (name == 1122) printf("%.*G \n",digits,sumaa+sumbb);
	if (name == 112233) printf("%.*G \n",digits,sumaa+sumbb+sumcc);
	if (name == 111) printf("%.*G \n",digits,sumaa+suma);
	if (name == -1) printf("%.*G \n",digits,temp);
	if (name == -12) printf("%.*G \n",digits,temp+sumb);

}

int init(char* name)
{
	TYPE any=0.;
	TYPE zero=0.;
	TYPE half=.5;
	TYPE one=1.;
	TYPE two=2.;
	TYPE small = .000001;
	int unit =1;
	int frac=-1;
	int frac2=-2;

	if	(!strcmp(name, "s000 ")) {
	  for (int i = 0; i < lll; i++) {
            X[i] = 1+i;
            Y[i] = 2+i;
            Z[i] = 3+i;
            U[i] = 4+i;
            V[i] = 5+i;
          }
	} else if (!strcmp(name, "s111 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac2);
		set1d(c, any,frac2);
		set1d(d, any,frac2);
		set1d(e, any,frac2);
	} else if (!strcmp(name, "s112 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "s113 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "s114 ")) {
		set2d(aa, any,frac);
		set2d(bb, any,frac2);
	} else if (!strcmp(name, "s115 ")) {
		set1d(a, one,unit);
		set2d(aa,small,unit);
		set2d(bb,small,unit);
		set2d(cc,small,unit);
	} else if (!strcmp(name, "s116 ")) {
		set1d(a, one,unit);
	} else if (!strcmp(name, "s118 ")) {
		set1d(a, one,unit);
		set2d(bb,small,unit);
	} else if (!strcmp(name, "s119 ")) {
		set2d(aa, one,unit);
		set2d(bb, any,frac2);
	} else if (!strcmp(name, "s121 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "s122 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "s123 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
		set1d(c, one,unit);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s124 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
		set1d(c, one,unit);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s125 ")) {
		set1ds(LEN*LEN, array,zero,unit);
		set2d(aa, one,unit);
		set2d(bb,half,unit);
		set2d(cc, two,unit);
	} else if (!strcmp(name, "s126 ")) {
		set2d(bb, one,unit);
		set1ds(LEN*LEN,array,any,frac);
		set2d(cc, any,frac);
	} else if (!strcmp(name, "s127 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
		set1d(c, any,frac);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s128 ")) {
		set1d(a,zero,unit);
		set1d(b, two,unit);
		set1d(c, one,unit);
		set1d(d, one,unit);
	} else if (!strcmp(name, "s131 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "s132 ")) {
		set2d(aa, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
	} else if (!strcmp(name, "s141 ")) {
		set1ds(LEN*LEN,array, one,unit);
		set2d(bb, any,frac2);
	} else if (!strcmp(name, "s151 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "s152 ")) {
		set1d(a, one,unit);
		set1d(b,zero,unit);
		set1d(c, any,frac);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s161 ")) {
		set1d(a, one,unit);
		set1ds(LEN/2,&b[0], one,2);
		set1ds(LEN/2,&b[1],-one,2);
		set1d(c, one,unit);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s162 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
	} else if (!strcmp(name, "s171 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "s172 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "s173 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "s174 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "s175 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "s176 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
	} else if (!strcmp(name, "s211 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
		set1d(c, any,frac);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s212 ")) {
		set1d(a, any,frac);
		set1d(b, one,unit);
		set1d(c, one,unit);
		set1d(d, any,frac);
	} else if (!strcmp(name, "s221 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
		set1d(d, any,frac);
	} else if (!strcmp(name, "s222 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
		set1d(c, one,unit);
	} else if (!strcmp(name, "s231 ")) {
		set2d(aa, one,unit);
		set2d(bb, any,frac2);
	} else if (!strcmp(name, "s232 ")) {
		set2d(aa, one,unit);
		set2d(bb,zero,unit);
	} else if (!strcmp(name, "s233 ")) {
		set2d(aa, any,frac);
		set2d(bb, any,frac);
		set2d(cc, any,frac);
	} else if (!strcmp(name, "s234 ")) {
		set2d(aa, one,unit);
		set2d(bb, any,frac);
		set2d(cc, any,frac);
	} else if (!strcmp(name, "s235 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
		set2d(aa, one,unit);
		set2d(bb, any, frac2);
	} else if (!strcmp(name, "s241 ")) {
		set1d(a, one,unit);
		set1d(b, one,unit);
		set1d(c, one,unit);
		set1d(d, one,unit);
	} else if (!strcmp(name, "s242 ")) {
		set1d(a,small,unit);
		set1d(b,small,unit);
		set1d(c,small,unit);
		set1d(d,small,unit);
	} else if (!strcmp(name, "s243 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
		set1d(c, any,frac);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s244 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
		set1d(c,small,unit);
		set1d(d,small,unit);
	} else if (!strcmp(name, "s251 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
		set1d(c, any,frac);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s252 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
		set1d(c, one,unit);
	} else if (!strcmp(name, "s253 ")) {
		set1d(a, one,unit);
		set1d(b,small,unit);
		set1d(c, one,unit);
		set1d(d, any,frac);
	} else if (!strcmp(name, "s254 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
	} else if (!strcmp(name, "s255 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
	} else if (!strcmp(name, "s256 ")) {
		set1d(a, one,unit);
		set2d(aa, two,unit);
		set2d(bb, one,unit);
	} else if (!strcmp(name, "s257 ")) {
		set1d(a, one,unit);
		set2d(aa, two,unit);
		set2d(bb, one,unit);
	} else if (!strcmp(name, "s258 ")) {
		set1d(a, any,frac);
		set1d(b,zero,unit);
		set1d(c, any,frac);
		set1d(d, any,frac);
		set1d(e,zero,unit);
		set2d(aa, any,frac);
	} else if (!strcmp(name, "s261 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac2);
		set1d(c, any,frac2);
		set1d(d, one,unit);
	} else if (!strcmp(name, "s271 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
	} else if (!strcmp(name, "s272 ")) {
		set1d(a, one,unit);
		set1d(b, one,unit);
		set1d(c, any,frac);
		set1d(d, any,frac);
		set1d(e, two,unit);
	} else if (!strcmp(name, "s273 ")) {
		set1d(a, one,unit);
		set1d(b, one,unit);
		set1d(c, one,unit);
		set1d(d,small,unit);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s274 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
		set1d(c, one,unit);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s275 ")) {
		set2d(aa, one,unit);
		set2d(bb,small,unit);
		set2d(cc,small,unit);
	} else if (!strcmp(name, "s276 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
		set1d(d, any,frac);
	} else if (!strcmp(name, "s277 ")) {
		set1d(a, one,unit);
		set1ds(LEN/2,b, one,unit);
		set1ds(LEN/2,&b[LEN/2],-one,unit);
		set1d(c, any,frac);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s278 ")) {
		set1ds(LEN/2,a,-one,unit);
		set1ds(LEN/2,&a[LEN/2],one,unit);
		set1d(b, one,unit);
		set1d(c, any,frac);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s279 ")) {
		set1ds(LEN/2,a,-one,unit);
		set1ds(LEN/2,&a[LEN/2],one,unit);
//		set1d(a, -one,unit);
		set1d(b, one,unit);
		set1d(c, any,frac);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s2710")) {
		set1d(a, one,unit);
		set1d(b, one,unit);
		set1d(c, any,frac);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s2711")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
	} else if (!strcmp(name, "s2712")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
	} else if (!strcmp(name, "s281 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
		set1d(c, one,unit);
	} else if (!strcmp(name, "s291 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
	} else if (!strcmp(name, "s292 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
	} else if (!strcmp(name, "s293 ")) {
		set1d(a, any,frac);
	} else if (!strcmp(name, "s2101")) {
		set2d(aa, one,unit);
		set2d(bb, any,frac);
		set2d(cc, any,frac);
	} else if (!strcmp(name, "s2102")) {
		set2d(aa,zero,unit);
	} else if (!strcmp(name, "s2111")) {
//		set2d(aa, one,unit);
		set2d(aa,zero,unit);
	} else if (!strcmp(name, "s311 ")) {
		set1d(a, any,frac);
	} else if (!strcmp(name, "s312 ")) {
		set1d(a,1.000001,unit);
	} else if (!strcmp(name, "s313 ")) {
		set1d(a, any,frac);
		set1d(b, any,frac);
	} else if (!strcmp(name, "s314 ")) {
		set1d(a, any,frac);
	} else if (!strcmp(name, "s315 ")) {
		set1d(a, any,frac);
	} else if (!strcmp(name, "s316 ")) {
		set1d(a, any,frac);
	} else if (!strcmp(name, "s317 ")) {
	} else if (!strcmp(name, "s318 ")) {
		set1d(a, any,frac);
		a[LEN-1] = -two;
	} else if (!strcmp(name, "s319 ")) {
		set1d(a,zero,unit);
		set1d(b,zero,unit);
		set1d(c, any,frac);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s3110")) {
		set2d(aa, any,frac);
		aa[LEN2-1][LEN2-1] = two;
	} else if (!strcmp(name, "s3111")) {
		set1d(a, any,frac);
	} else if (!strcmp(name, "s3112")) {
		set1d(a, any,frac2);
		set1d(b,zero,unit);
	} else if (!strcmp(name, "s3113")) {
		set1d(a, any,frac);
		a[LEN-1] = -two;
	} else if (!strcmp(name, "s321 ")) {
		set1d(a, one,unit);
		set1d(b,zero,unit);
	} else if (!strcmp(name, "s322 ")) {
		set1d(a, one,unit);
		set1d(b,zero,unit);
		set1d(c,zero,unit);
	} else if (!strcmp(name, "s323 ")) {
		set1d(a, one,unit);
		set1d(b, one,unit);
		set1d(c, any,frac);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s331 ")) {
		set1d(a, any,frac);
		a[LEN-1] = -one;
	} else if (!strcmp(name, "s332 ")) {
		set1d(a, any,frac2);
		a[LEN-1] = two;
	} else if (!strcmp(name, "s341 ")) {
		set1d(a,zero,unit);
		set1d(b, any,frac);
	} else if (!strcmp(name, "s342 ")) {
		set1d(a, any,frac);
		set1d(b, any,frac);
	} else if (!strcmp(name, "s343 ")) {
		set2d(aa, any,frac);
		set2d(bb, one,unit);
	} else if (!strcmp(name, "s351 ")) {
		set1d(a, one,unit);
		set1d(b, one,unit);
		c[0] = 1.;
	} else if (!strcmp(name, "s352 ")) {
		set1d(a, any,frac);
		set1d(b, any,frac);
	} else if (!strcmp(name, "s353 ")) {
		set1d(a, one,unit);
		set1d(b, one,unit);
		c[0] = 1.;
	} else if (!strcmp(name, "s411 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
	} else if (!strcmp(name, "s412 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
	} else if (!strcmp(name, "s413 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
		set1d(c, one,unit);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s414 ")) {
		set2d(aa, one,unit);
		set2d(bb, any,frac);
		set2d(cc, any,frac);
	} else if (!strcmp(name, "s415 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
		a[LEN-1] = -one;
	} else if (!strcmp(name, "s421 ")) {
		set1d(a, any,frac2);
		set1d(b, one,unit);
	} else if (!strcmp(name, "s422 ")) {
		set1d(array,one,unit);
		set1d(a, any,frac2);
	} else if (!strcmp(name, "s423 ")) {
		set1d(array,zero,unit);
		set1d(a, any,frac2);
	} else if (!strcmp(name, "s424 ")) {
		set1d(array,one,unit);
		set1d(a, any,frac2);
	} else if (!strcmp(name, "s431 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "s432 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "s441 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
		set1ds(LEN/3,	&d[0],		-one,unit);
		set1ds(LEN/3,	&d[LEN/3],	zero,unit);
		set1ds(LEN/3+1, &d[(2*LEN/3)], one,unit);
	} else if (!strcmp(name, "s442 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s443 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
	} else if (!strcmp(name, "s451 ")) {
		set1d(b, any,frac);
		set1d(c, any,frac);
	} else if (!strcmp(name, "s452 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
		set1d(c,small,unit);
	} else if (!strcmp(name, "s453 ")) {
		set1d(a,zero,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "s471 ")) {
		set1d(a, one,unit);
		set1d(b, one,unit);
		set1d(c, one,unit);
		set1d(d, any,frac);
		set1d(e, any,frac);
	} else if (!strcmp(name, "s481 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
		set1d(d, any,frac);
	} else if (!strcmp(name, "s482 ")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
	} else if (!strcmp(name, "s491 ")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
		set1d(c, any,frac);
		set1d(d, any,frac);
	} else if (!strcmp(name, "s4112")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
	} else if (!strcmp(name, "s4113")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
		set1d(c, any,frac2);
	} else if (!strcmp(name, "s4114")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
		set1d(c, any,frac);
		set1d(d, any,frac);
	} else if (!strcmp(name, "s4115")) {
		set1d(a, any,frac);
		set1d(b, any,frac);
	} else if (!strcmp(name, "s4116")) {
		set1d(a, any,frac);
		set2d(aa, any,frac);
	} else if (!strcmp(name, "s4117")) {
		set1d(a,zero,unit);
		set1d(b, one,unit);
		set1d(c, any,frac);
		set1d(d, any,frac);
	} else if (!strcmp(name, "s4121")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
	} else if (!strcmp(name, "va	")) {
		set1d(a,zero,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "vag  ")) {
		set1d(a,zero,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "vas  ")) {
		set1d(a,zero,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "vif  ")) {
		set1d(a,zero,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "vpv  ")) {
		set1d(a,zero,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "vtv  ")) {
		set1d(a, one,unit);
		set1d(b, one,unit);
	} else if (!strcmp(name, "vpvtv")) {
		set1d(a, one,unit);
		set1d(b, any,frac);
		set1d(c, any,frac);
	} else if (!strcmp(name, "vpvts")) {
		set1d(a, one,unit);
		set1d(b, any,frac2);
	} else if (!strcmp(name, "vpvpv")) {
		set1d(a, any,frac2);
		set1d(b, one,unit);
		set1d(c,-one,unit);
	} else if (!strcmp(name, "vtvtv")) {
		set1d(a, one,unit);
		set1d(b, two,unit);
		set1d(c,half,unit);
	} else if (!strcmp(name, "vsumr")) {
		set1d(a, any,frac);
	} else if (!strcmp(name, "vdotr")) {
		set1d(a, any,frac);
		set1d(b, any,frac);
	} else if (!strcmp(name, "vbor ")) {
		set1d(a, any,frac);
		set1d(b, any,frac);
		set1d(c, one,frac);
		set1d(d, two,frac);
		set1d(e,half,frac);
		set2d(aa, any,frac);
	} else {
	}

	return 0;
}

void set(int* ip, TYPE* s1, TYPE* s2){
        posix_memalign((void **) &xx, ALIGNMENT, LEN*sizeof(TYPE));
	printf("\n");
	for (int i = 0; i < LEN; i = i+5){
		ip[i]	= (i+4);
		ip[i+1] = (i+2);
		ip[i+2] = (i);
		ip[i+3] = (i+3);
		ip[i+4] = (i+1);

	}

	set1d(a, 1.,1);
	set1d(b, 1.,1);
	set1d(c, 1.,1);
	set1d(d, 1.,1);
	set1d(e, 1.,1);
	set2d(aa, 0.,-1);
	set2d(bb, 0.,-1);
	set2d(cc, 0.,-1);

	for (int i = 0; i < LEN; i++){
		indx[i] = (i+1) % 4+1;
	}
	*s1 = 1.0;
	*s2 = 2.0;

}

// #if TESTS & LINEAR_DEPENDENCE
extern int s000();
extern int s111();
extern int s1111();
extern int s112();
extern int s1112();
extern int s113();
extern int s1113();
extern int s114();
extern int s115();
extern int s1115();
extern int s116();
extern int s118();
extern int s119();
extern int s1119();
// #endif
// #if TESTS & INDUCTION_VARIABLE
extern int s121();
extern int s122(int, int);
extern int s123();
extern int s124();
extern int s125();
extern int s126();
extern int s127();
extern int s128();
// #endif
// #if TESTS & GLOBAL_DATA_FLOW
extern int s131();
extern int s132();
extern int s141();
extern int s151();
extern int s152();
// #endif
// #if TESTS & CONTROL_FLOW
extern int s161();
extern int s1161();
extern int s162(int);
// #endif
// #if TESTS & SYMBOLICS
extern int s171(int);
extern int s172(int,int);
extern int s173();
extern int s174(int);
extern int s175(int);
extern int s176();
// #endif
// #if TESTS & STATEMENT_REORDERING
extern int s211();
extern int s212();
extern int s1213();
// #endif
// #if TESTS & LOOP_RESTRUCTURING
extern int s221();
extern int s1221();
extern int s222();
extern int s231();
extern int s232();
extern int s1232();
extern int s233();
extern int s2233();
extern int s235();
// #endif
// #if TESTS & NODE_SPLITTING
extern int s241();
extern int s242(TYPE, TYPE);
extern int s243();
extern int s244();
extern int s1244();
extern int s2244();
// #endif
// #if TESTS & EXPANSION
extern int s251();
extern int s1251();
extern int s2251();
extern int s3251();
extern int s252();
extern int s253();
extern int s254();
extern int s255();
extern int s256();
extern int s257();
extern int s258();
extern int s261();
// #endif
// #if TESTS & CONTROL_FLOW
extern int s271();
extern int s272(TYPE);
extern int s273();
extern int s274();
extern int s275();
extern int s2275();
extern int s276();
extern int s277();
extern int s278();
extern int s279();
extern int s1279();
extern int s2710(TYPE);
extern int s2711();
extern int s2712();
// #endif
// #if TESTS & CROSSING_THRESHOLDS
extern int s281();
extern int s1281();
extern int s291();
extern int s292();
extern int s293();
extern int s2101();
extern int s2102();
extern int s2111();
// #endif
// #if TESTS & REDUCTIONS
extern int s311();
extern int s31111();
extern int s312();
extern int s313();
extern int s314();
extern int s315();
extern int s316();
extern int s317();
extern int s318(int);
extern int s319();
extern int s3110();
extern int s13110();
extern int s3111();
extern int s3112();
extern int s3113();
// #endif
// #if TESTS & RECURRENCES
extern int s321();
extern int s322();
extern int s323();
// #endif
// #if TESTS & SEARCHING
extern int s331();
extern int s332(TYPE);
// #endif
// #if TESTS & PACKING
extern int s341();
extern int s342();
extern int s343();
// #endif
// #if TESTS & LOOP_REROLLING
extern int s351();
extern int s1351();
extern int s352();
extern int s353(int*);
// #endif
// #if TESTS & EQUIVALENCING
extern int s421();
extern int s1421();
extern int s422();
extern int s423();
extern int s424();
// #endif
// #if TESTS & GLOBAL_DATA_FLOW
extern int s431();
// #endif
// #if TESTS & CONTROL_FLOW
extern int s441();
extern int s442();
extern int s443();
// #endif
// #if TESTS & GLOBAL_DATA_FLOW
extern int s451();
extern int s452();
// #endif
// #if TESTS & INDUCTION_VARIABLE
extern int s453();
// #endif
// #if TESTS & GLOBAL_DATA_FLOW
extern int s471();
// #endif
// #if TESTS & CONTROL_FLOW
extern int s481();
extern int s482();
// #endif
// #if TESTS & INDIRECT_ADDRESSING
extern int s491(int*);
extern int s4112(int*, TYPE);
extern int s4113(int*);
extern int s4114(int*,int);
extern int s4115(int*);
extern int s4116(int*, int, int);
extern int s4117();
// #endif
// #if TESTS & GLOBAL_DATA_FLOW
extern int s4121();
// #endif
// #if TESTS & CONTROL_LOOPS
extern int va();
extern int vag(int*);
extern int vas(int*);
extern int vif();
extern int vpv();
extern int vtv();
extern int vpvtv();
extern int vpvts(TYPE);
extern int vpvpv();
extern int vtvtv();
extern int vsumr();
extern int vdotr();
extern int vbor();
// #endif

int main(int argc, char *argv[]){
	int n1 = 1;
	int n3 = 1;
	int* ip;
	TYPE s1,s2;

	posix_memalign((void **) &ip, ALIGNMENT, LEN*sizeof(TYPE));

	if (argc > 1)
		ntimes = atoi(argv[1]);
	printf("Running each loop %d times...\n", ntimes);

	if (argc > 2)
		digits = atoi(argv[2]);

	set(ip, &s1, &s2);
	printf("Loop \t Time(Sec) \t Checksum \n");

#if LOOPs000
	s000();
#elif LOOPs111
	s111();
#elif LOOPs1111
	s1111();
#elif LOOPs112
	s112();
#elif LOOPs1112
	s1112();
#elif LOOPs113
	s113();
#elif LOOPs1113
	s1113();
#elif LOOPs114
	s114();
#elif LOOPs115
	s115();
#elif LOOPs1115
	s1115();
#elif LOOPs116
	s116();
#elif LOOPs118
	s118();
#elif LOOPs119
	s119();
#elif LOOPs1119
	s1119();
#elif LOOPs121
	s121();
#elif LOOPs122
	s122(n1,n3);
#elif LOOPs123
	s123();
#elif LOOPs124
	s124();
#elif LOOPs125
	s125();
#elif LOOPs126
	s126();
#elif LOOPs127
	s127();
#elif LOOPs128
	s128();
#elif LOOPs131
	s131();
#elif LOOPs132
	s132();
#elif LOOPs141
	s141();
#elif LOOPs151
	s151();
#elif LOOPs152
	s152();
#elif LOOPs161
	s161();
#elif LOOPs1161
	s1161();
#elif LOOPs162
	s162(n1);
#elif LOOPs171
	s171(n1);
#elif LOOPs172
	s172(n1,n3);
#elif LOOPs173
	s173();
#elif LOOPs174
	s174(LEN/2);
#elif LOOPs175
	s175(n1);
#elif LOOPs176
	s176();
#elif LOOPs211
	s211();
#elif LOOPs212
	s212();
#elif LOOPs1213
	s1213();
#elif LOOPs221
	s221();
#elif LOOPs1221
	s1221();
#elif LOOPs222
	s222();
#elif LOOPs231
	s231();
#elif LOOPs232
	s232();
#elif LOOPs1232
	s1232();
#elif LOOPs233
	s233();
#elif LOOPs2233
	s2233();
#elif LOOPs235
	s235();
#elif LOOPs241
	s241();
#elif LOOPs242
	s242(s1, s2);
#elif LOOPs243
	s243();
#elif LOOPs244
	s244();
#elif LOOPs1244
	s1244();
#elif LOOPs2244
	s2244();
#elif LOOPs251
	s251();
#elif LOOPs1251
	s1251();
#elif LOOPs2251
	s2251();
#elif LOOPs3251
	s3251();
#elif LOOPs252
	s252();
#elif LOOPs253
	s253();
#elif LOOPs254
	s254();
#elif LOOPs255
	s255();
#elif LOOPs256
	s256();
#elif LOOPs257
	s257();
#elif LOOPs258
	s258();
#elif LOOPs261
	s261();
#elif LOOPs271
	s271();
#elif LOOPs272
	s272(s1);
#elif LOOPs273
	s273();
#elif LOOPs274
	s274();
#elif LOOPs275
	s275();
#elif LOOPs2275
	s2275();
#elif LOOPs276
	s276();
#elif LOOPs277
	s277();
#elif LOOPs278
	s278();
#elif LOOPs279
	s279();
#elif LOOPs1279
	s1279();
#elif LOOPs2710
	s2710(s1);
#elif LOOPs2711
	s2711();
#elif LOOPs2712
	s2712();
#elif LOOPs281
	s281();
#elif LOOPs1281
	s1281();
#elif LOOPs291
	s291();
#elif LOOPs292
	s292();
#elif LOOPs293
	s293();
#elif LOOPs2101
	s2101();
#elif LOOPs2102
	s2102();
#elif LOOPs2111
	s2111();
#elif LOOPs311
	s311();
#elif LOOPs31111
	s31111();
#elif LOOPs312
	s312();
#elif LOOPs313
	s313();
#elif LOOPs314
	s314();
#elif LOOPs315
	s315();
#elif LOOPs316
	s316();
#elif LOOPs317
	s317();
#elif LOOPs318
	s318(n1);
#elif LOOPs319
	s319();
#elif LOOPs3110
	s3110();
#elif LOOPs13110
	s13110();
#elif LOOPs3111
	s3111();
#elif LOOPs3112
	s3112();
#elif LOOPs3113
	s3113();
#elif LOOPs321
	s321();
#elif LOOPs322
	s322();
#elif LOOPs323
	s323();
#elif LOOPs331
	s331();
#elif LOOPs332
	s332(s1);
#elif LOOPs341
	s341();
#elif LOOPs342
	s342();
#elif LOOPs343
	s343();
#elif LOOPs351
	s351();
#elif LOOPs1351
	s1351();
#elif LOOPs352
	s352();
#elif LOOPs353
	s353(ip);
#elif LOOPs421
	s421();
#elif LOOPs1421
	s1421();
#elif LOOPs422
	s422();
#elif LOOPs423
	s423();
#elif LOOPs424
	s424();
#elif LOOPs431
	s431();
#elif LOOPs441
	s441();
#elif LOOPs442
	s442();
#elif LOOPs443
	s443();
#elif LOOPs451
	s451();
#elif LOOPs452
	s452();
#elif LOOPs453
	s453();
#elif LOOPs471
	s471();
#elif LOOPs481
	s481();
#elif LOOPs482
	s482();
#elif LOOPs491
	s491(ip);
#elif LOOPs4112
	s4112(ip, s1);
#elif LOOPs4113
	s4113(ip);
#elif LOOPs4114
	s4114(ip,n1);
#elif LOOPs4115
	s4115(ip);
#elif LOOPs4116
	s4116(ip, LEN2/2, n1);
#elif LOOPs4117
	s4117();
#elif LOOPs4121
	s4121();
#elif LOOPva
	va();
#elif LOOPvag
	vag(ip);
#elif LOOPvas
	vas(ip);
#elif LOOPvif
	vif();
#elif LOOPvpv
	vpv();
#elif LOOPvtv
	vtv();
#elif LOOPvpvtv
	vpvtv();
#elif LOOPvpvts
	vpvts(s1);
#elif LOOPvpvpv
	vpvpv();
#elif LOOPvtvtv
	vtvtv();
#elif LOOPvsumr
	vsumr();
#elif LOOPvdotr
	vdotr();
#elif LOOPvbor
	vbor();
#endif
}
