#include <time.h>

#ifndef TYPES_H
#define TYPES_H

#define LEN 32000
#define LEN_1D 32000
#define LEN2 256
#define LEN_2D 256

#ifndef TYPE
  #define TYPE float
  #define FABS(x) fabsf(x)
#else
  #define FABS(x) fabs(x)
#endif

#ifndef X_TYPE
  #define X_TYPE TYPE
#endif

#ifndef ALIGNMENT
#define ALIGNMENT 16
#endif

#define lll LEN

#endif // TYPES_H
