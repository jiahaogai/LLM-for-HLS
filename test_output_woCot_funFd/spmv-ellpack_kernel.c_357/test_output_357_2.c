Code: #pragma ACCEL PARAMS ellpack_nzval=auto{4940} ellpack_cols=auto{4940} ellpack_vec=auto{494} ellpack_out=auto{494}:
   User-provided parameters for the function ellpack. The values of these parameters are automatically passed to the function at runtime.

#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
 #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{4}

#pragma ACCEL PARALLEL FACTOR=auto{1}
 #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{16}
 #pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{4}

#pragma ACCEL PARALLEL FACTOR=auto{1}
 #pragma ACCEL PIPELINE auto{off}
#include <math.h>
#pragma ACCEL kernel
void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 32; j++) {
      sum += nzval[(i * 16 + j)] * vec[cols[(i * 16 + j)]];
    }
    out[i] = sum;
  }
}