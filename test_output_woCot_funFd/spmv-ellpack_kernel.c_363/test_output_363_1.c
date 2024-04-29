#include <math.h>
#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
<<<<<<< HEAD
  double sum;
  double nzval_tmp;
  int cols_tmp;
=======
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{494}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    for (j = 0; j < 32; j++) {
      nzval_tmp = nzval[i * 32 + j];
      cols_tmp = cols[i * 32 + j];
      sum += nzval_tmp * vec[cols_tmp];
    }
    out[i] = sum;
=======
  for (j = 0; j < 4940; j++) {
    out[cols[j]] += nzval[j] * vec[j / 64];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}