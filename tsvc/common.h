#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "math.h"

extern int ntimes;
extern X_TYPE X[lll],Y[lll],Z[lll],U[lll],V[lll];

extern TYPE x[LEN] __attribute__((aligned(ALIGNMENT)));
extern TYPE temp;
extern TYPE* __restrict__ xx;
extern TYPE* yy;
extern int indx[LEN] __attribute__((aligned(ALIGNMENT)));
extern TYPE array[LEN2*LEN2] __attribute__((aligned(ALIGNMENT)));

__attribute__((aligned(ALIGNMENT))) extern TYPE * const a;
__attribute__((aligned(ALIGNMENT))) extern TYPE * const b;
__attribute__((aligned(ALIGNMENT))) extern TYPE * const c;
__attribute__((aligned(ALIGNMENT))) extern TYPE * const d;
__attribute__((aligned(ALIGNMENT))) extern TYPE * const e;
__attribute__((aligned(ALIGNMENT))) extern TYPE (* const aa)[LEN2];
__attribute__((aligned(ALIGNMENT))) extern TYPE (* const bb)[LEN2];
__attribute__((aligned(ALIGNMENT))) extern TYPE (* const cc)[LEN2];
__attribute__((aligned(ALIGNMENT))) extern TYPE (* const tt)[LEN2];

extern int init(char *);
extern void check(int);
extern int set1d(TYPE[LEN], TYPE, int);
extern int dummy(TYPE[LEN], TYPE[LEN], TYPE[LEN], TYPE[LEN], TYPE[LEN], TYPE[LEN2][LEN2], TYPE[LEN2][LEN2], TYPE[LEN2][LEN2], TYPE);
