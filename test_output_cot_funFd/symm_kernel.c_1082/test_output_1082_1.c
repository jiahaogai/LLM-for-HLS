Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{2}
Code: #pragma ACCEL PARALLEL FACTOR=auto{10}
Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{32}
Code: #pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
Code: #pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
 #pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{16}
    for (j = 0; j < 60; j++) {
      temp1 = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{32}
      for (k = 0; k < 80; ++k) {
        temp1 += A[i][k] * B[k][j];
      }
      temp2 = alpha * temp1 + beta * C[i][j];
      temp2 = temp2;
      C[i][j] = temp2;
    }
  }
}