#include <math.h>
#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double nzval_tmp;
  int cols_tmp;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{494}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    for (j = cols[i]; j < cols[i + 1]; j++) {
      nzval_tmp = nzval[j];
      cols_tmp = cols[j];
    }
    out[i] = sum;
  }
}