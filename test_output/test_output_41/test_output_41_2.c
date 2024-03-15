 
 #pragma ACCEL PARALLEL FACTOR=auto{1}
  for (tj = 1; tj <= 20; tj++) {
    tmp2 = 0.0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (ti = 1; ti <= 40; ti++) {
      tmp2 += A[tj][ti] * x[ti];
    }
    y[tj] = 0.0;
    sum = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L3}
    for (ti = 1; ti <= 40; ti++) {
      sum += B[tj][ti] * A[tj][ti];
      y[tj] += pow(B[tj][ti],2) * x[ti] + sum;
    }
  }
}
