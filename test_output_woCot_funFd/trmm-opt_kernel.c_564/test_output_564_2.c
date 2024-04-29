Code: #pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{16}
    for (j = 0; j < 80; j++) {
      sum = 0.0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{80}
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{60}
      for (k = 0; k < 60; k++) {
        sum += A[i][k] * B[k][j];
      }
      tmp[i][j] = sum;
    }
  }
}