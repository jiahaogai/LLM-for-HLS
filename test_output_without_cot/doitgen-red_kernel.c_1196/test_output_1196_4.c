#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

  
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{30}
  for (r = 0; r < 30; r++) {
    sum_tmp = sum[r];
    
#pragma ACCEL PARALLEL reduction=C4_tmp FACTOR=auto{1}
    for (q = 0; q < 30; q++) {
      C4_tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=A_tmp FACTOR=auto{1}
      for (s = 0; s < 20; s++) {
        A_tmp = 0.0;
#pragma ACCEL PARALLEL FACTOR=auto{1}
	for (p = 0; p < 25; p++) {
          A_tmp += A[p][s][r] * B[q][p];
        }
	for (p = 0; p < 25; p++) {
          C4[p][q] += A_tmp * D[p][s];
        }
	C4_tmp += C4[s][q];
      }
      sum[r] = sum_tmp + C4_tmp;
    }
  }
}