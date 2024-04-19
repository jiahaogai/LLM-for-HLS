4. `#pragma ACCEL PARALLEL FACTOR=auto{32} PARALLEL FACTOR=auto{16} PIPELINE auto{off} PARALLEL FACTOR=auto{4}` - 
   
#pragma ACCEL PIPELINE auto{off}
   
#pragma ACCEL TILE FACTOR=auto{1}
   for (i = 0; i < 40; i++) {

#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 0; j < 50; j++) {
         tmp[i][j] = 0.0;
         
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{32}
         for (k = 0; k < 70; ++k) {
            tmp[i][j] += alpha * A[i][k] * B[k][j];
         }
      }
   }

#pragma ACCEL PIPELINE auto{off}
   
#pragma ACCEL TILE FACTOR=auto{1}
   for (i = 0; i < 40; i++) {

#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 0; j < 80; j++) {
         D[i][j] *= beta;
         
#pragma ACCEL PARALLEL FACTOR=auto{16}
         for (k = 0; k < 50; ++k) {
            D[i][j] += tmp[i][k] * C[k][j];
         }
      }
   }