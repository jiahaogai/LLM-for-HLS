#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}

  for (r = 0; r < 30; r++) {
    sum_tmp = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{2}
    for (q = 0; q < 20; q++) {
      sum_tmp += A[0][q][r] * C4[q][r];
    }
    
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{__PARA__L2}
    for (s = 0; s < 25; s++) {
      sum_tmp += A[s][19][r] * C4[19][r];
    }
    sum[r] = sum_tmp;
  }
}