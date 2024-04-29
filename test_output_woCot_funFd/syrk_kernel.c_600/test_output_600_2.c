Code: #pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
   for (i = 0; i < 80; i++) {
      for (j = 0; j < 80; j++) {
         C[i][j] *= beta;
      }
   }
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{flatten}
#pragma ACCEL TILE FACTOR=auto{8}
#pragma ACCEL PARALLEL FACTOR=auto{4}
   for (i = 0; i < 60; i++) {
      for (j = 0; j < 80; j++) {
         tmp = A[i][j];
         sum = 0.0;
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
	 for (k = 0; k < 80; k++) {
            sum += A[k][j] * tmp;
         }
	 C[i][j] = sum;
      }
   }
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
   for (i = 0; i < 80; i++) {
      for (j = 0; j < 80; j++) {
         C[i][j] *= beta;
      }
   }
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{flatten}
#pragma ACCEL TILE FACTOR=auto{8}
#pragma ACCEL PARALLEL FACTOR=auto{4}
   for (i = 0; i < 60; i++) {
      for (j = 0; j < 80; j++) {
         tmp = A[i][j];
         sum = 0.0;
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
	 for (k = 0; k < 80; k++) {
            sum += A[k][j] * tmp;
         }
	 C[i][j] = sum;
      }
   }