
 #pragma ACCEL PIPELINE auto{__PIPE__L0}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L0}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (r = 0; r < 128; r++) {
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{__PARA__L2}
    for (q = 0; q < 128; q++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction FACTOR=auto{__PARA__L3}
      for (p = 0; p < 128; p++) {
        sum += A[p][r] * B[r][q];
      }
      C[r][q] = sum;
    }
    for (q = 0; q < 128; q++) {
      double tmp = 0.0;
      for (p = 0; p < 128; p++) {
        tmp += A[p][r] * C[p][q];
      }
      D[r][q] = tmp;
    }
  }
}
