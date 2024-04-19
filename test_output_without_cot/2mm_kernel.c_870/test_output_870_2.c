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

    for (l = 0; l < 80; l++) {
      D[i][l] *= beta;
      
#pragma ACCEL PARALLEL reduction = D FACTOR=auto{50}
      for (j = 0; j < 50; j++) {
        D[i][l] += tmp[i][j] * C[j][l];
      }
    }
  }
}