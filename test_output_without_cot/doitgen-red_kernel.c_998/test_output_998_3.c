#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{2}
  for (r = 0; r < 30; r++) {
    sum_tmp = 0.0;
    
#pragma ACCEL PARALLEL reduction=A_tmp FACTOR=auto{__PARA__L2}
    for (q = 0; q < 20; q++) {
      A_tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=b_tmp FACTOR=auto{__PARA__L3}
      for (p = 0; p < 25; p++) {
        b_tmp = A[p][q][r];
        A_tmp += b_tmp * B[p];
      }
      e = A_tmp * F[q];
      sum_tmp += e;
      C4[r][q] = sum_tmp;
    }
    sum[r] = sum_tmp;
  }
}