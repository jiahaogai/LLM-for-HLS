#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}

  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}

    for (j = 0; j < 50; j++) {
      tmp[i][j] = 0.0;
      
#pragma ACCEL PARALLEL reduction = tmp FACTOR=auto{1}
      for (k = 0; k < 70; ++k) {
        tmp[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}

    for (j = 0; j < 80; j++) {
      D[i][j] *= beta;
      
#pragma ACCEL PARALLEL reduction = D FACTOR=auto{50}
      for (k = 0; k < 50; ++k) {
        D[i][j] += C[k][j] * tmp[i][k];
      }
    }
  }
}