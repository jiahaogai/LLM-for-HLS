Code: #pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{2}
    for (j = 0; j < 240; j++) {
      temp1[i][j] = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{8}
      for (k = 0; k < 200; k++) {
        temp1[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{5}
    for (j = 0; j < 240; j++) {
      temp2[i][j] = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{8}
      for (k = 0; k < 240; k++) {
        temp2[i][j] += temp1[i][k] * B[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
    for (j = 0; j < 240; j++) {
      C[i][j] += temp2[i][j];
    }
  }
}