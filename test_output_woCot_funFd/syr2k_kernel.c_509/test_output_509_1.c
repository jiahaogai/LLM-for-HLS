#pragma ACCEL PIPELINE auto{off}
 #pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PARALLEL FACTOR=auto{80}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{2}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{60}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{4}
      for (j = 0; j < 80; j++) {
        A[i][j] += alpha * B[k][j] * A[i][k];
      }
    }
  }
//#pragma endscop
}